#include "drm_device.h"

static int _opengDevice(drm_dev_t * drm, const char *card) {
    drm->drmfd = open(card, O_RDWR | O_CLOEXEC);
    if (drm->drmfd < 0) {
        fprintf(stderr, "cannot open '%s':\n", card);
        return -1;
    }
    printf("open fd success: %d\n", drm->drmfd);
    return 0;
}

static int _findCrtc(int fd, drmModeRes* res, drmModeConnector* conn, uint32_t* crtc_out) {
    /* first try the currently conected encoder+crtc */
    if (conn->encoder_id) {
        drmModeEncoder* enc = drmModeGetEncoder(fd, conn->encoder_id);
        if (enc && enc->crtc_id) {
            uint32_t crtc = enc->crtc_id;
            if (crtc >= 0) {
                drmModeFreeEncoder(enc);
                *crtc_out = crtc;
                return 0;
            }
        }
        drmModeFreeEncoder(enc);
    }
    
    for (int i = 0; i < conn->count_encoders; ++i) {
        drmModeEncoder* enc = drmModeGetEncoder(fd, conn->encoders[i]);
        if (!enc) {
            fprintf(stderr, "cannot retrieve encoder %u:%u (%d): %m\n", i, conn->encoders[i], errno);
            continue;
        }

        /* iterate all global CRTCs */
        for (int j = 0; j < res->count_crtcs; ++j) {
            /* check whether this CRTC works with the encoder */
            if (!(enc->possible_crtcs & (1 << j)))
                continue;

            /* we have found a CRTC, so save it and return */
            if (res->crtcs[j] >= 0) {
                drmModeFreeEncoder(enc);
                *crtc_out = res->crtcs[j];
                return 0;
            }
        }

        drmModeFreeEncoder(enc);
    }

    fprintf(stderr, "cannot find suitable CRTC for connector %u\n", conn->connector_id);
    return -1;
}


static int _getConnector(drm_dev_t * drm) {
    /* retrieve resources */
    drmModeRes* res = drmModeGetResources(drm->drmfd);
    if (!res) {
        fprintf(stderr, "cannot retrieve DRM resources (%d): %m\n", errno);
        return -1;
    }

    /* iterate all connectors */
    for (int i = 0; i < res->count_connectors; ++i) {
        /* get information for each connector */
        drmModeConnector* conn = drmModeGetConnector(drm->drmfd, res->connectors[i]);
        if (!conn) {
            fprintf(stderr, "cannot retrieve DRM connector %u:%u (%d): %m\n", i,res->connectors[i], errno);
            continue;
        }

        /* check if a monitor is connected */
        if (conn->connection != DRM_MODE_CONNECTED) {
            drmModeFreeConnector(conn);
            fprintf(stderr, "ignoring unused connector %u\n", conn->connector_id);
            continue;
        }

        /* check if there is at least one valid mode */
        if (!conn->count_modes) {
            drmModeFreeConnector(conn);
            fprintf(stderr, "no valid mode for connector %u\n", conn->connector_id);
            continue;
        }

        drm->dev = (ModesetDev *)malloc(sizeof(ModesetDev));
        if (!drm->dev) {
            fprintf(stderr, "no valid mode for connector %u\n", conn->connector_id);
            return -1;
        }

        drm->dev->conn = conn->connector_id;
        drm->dev->mode = conn->modes[0];

        /* find a crtc for this connector */
        if (_findCrtc(drm->drmfd, res, conn, &drm->dev->crtc)) {
            fprintf(stderr, "cannot setup device for connector %u:%u (%d): %m\n", i, res->connectors[i], errno);
            drmModeFreeConnector(conn);
            continue;
        }
        printf("drm->dev->crtc %d \n",drm->dev->crtc);
        drmModeFreeConnector(conn);
        break;
    }

    /* free resources again */
    drmModeFreeResources(res);
    return 0;
}

int pageFlip(drm_dev_t *drm, uint32_t fb_id, void* user_data) {
    int ret = drmModePageFlip(drm->drmfd, drm->dev->crtc, fb_id, DRM_MODE_PAGE_FLIP_EVENT, user_data);
    if (ret) {
        fprintf(stderr, "failed to queue page flip\n");
        return -1;
    }
    return 0;
}

int modeSetCrtc(drm_dev_t *drm, uint32_t fb_id) 
{
    drm->dev->saved_crtc = drmModeGetCrtc(drm->drmfd, drm->dev->crtc);
    printf("params %d,%d,%d,%d\n", drm->drmfd, drm->dev->crtc, fb_id, drm->dev->conn);
    int ret = drmModeSetCrtc(drm->drmfd, drm->dev->crtc, fb_id, 0, 0, &drm->dev->conn, 1, &drm->dev->mode);
    if (ret) {
        printf( "cannot set CRTC for connector %u (%d): %m\n", drm->dev->conn, errno);
        return -1;
    }
    return 0;
}

static void _freeModeSetCrtc(drm_dev_t *drm)
{
    drmModeSetCrtc(drm->drmfd, 
                    drm->dev->saved_crtc->crtc_id, 
                    drm->dev->saved_crtc->buffer_id, 
                    drm->dev->saved_crtc->x, 
                    drm->dev->saved_crtc->y, 
                    &drm->dev->conn, 
                    1, 
                    &drm->dev->saved_crtc->mode);
    drmModeFreeCrtc(drm->dev->saved_crtc);
    close(drm->drmfd);
}

Resolution *_getDisplaySize(drm_dev_t *drm) 
{
    Resolution *res = (Resolution *)malloc(sizeof(Resolution));
    if (!res) {
        return NULL;
    }

    res->height = drm->dev->mode.hdisplay;
    res->width  =drm->dev->mode.vdisplay;

    return res;
}

int GetFD(drm_dev_t *drm)
{
    return drm->drmfd;
}

static void _onModesetPageFlipEvent(int fd, unsigned int frame, unsigned int sec, unsigned int usec, void* data) {
    // DRMModesetter::Impl* self = static_cast<DRMModesetter::Impl *>(data);
    // self->DidPageFlip(sec, usec);
    printf("flip\n");
}


void drm_flush_wait(drm_dev_t * drm)
{
    struct pollfd pfd;
    pfd.fd = drm->drmfd;
    pfd.events = POLLIN;
    
    drm->evctx.version           = DRM_EVENT_CONTEXT_VERSION;
    drm->evctx.page_flip_handler = _onModesetPageFlipEvent;

    while(drm->req) {
        int ret;
        do {
            ret = poll(&pfd, 1, -1);
        } while(ret == -1 && errno == EINTR);

        if(ret > 0)
            drmHandleEvent(drm->drmfd, &drm->evctx);
        else {
            printf("poll failed: %s\n", strerror(errno));
            return;
        }
    }
}

int Run(drm_dev_t *drm, int fb_id1, int fb_id2) {
    fd_set fds;
    drmEventContext evctx = {};
    evctx.version = DRM_EVENT_CONTEXT_VERSION;
    evctx.page_flip_handler = _onModesetPageFlipEvent;
    int is_running = 1;
    int front_buffer_ = 0;

    while (is_running) {
        front_buffer_ ^= 1;
        if (!pageFlip(drm, fb_id2 ,NULL)) {
            printf("failed page flip.\n");
            return -1;
        }

        int page_flip_pending_ = 1;
        while (page_flip_pending_) {
            FD_ZERO(&fds);
            FD_SET(0, &fds);
            FD_SET(GetFD(drm), &fds);

            int ret = select(GetFD(drm) + 1, &fds, NULL, NULL, NULL);
            if (ret < 0) {
                //std::cout << "select err: " << std::strerror(errno) << '\n';
                return -1;
            } else if (ret == 0) {
                fprintf(stderr, "select timeout!\n");
                return -1;
            }

            if (FD_ISSET(0, &fds)) {
                is_running = 0;
            }

            if (FD_ISSET(GetFD(drm), &fds)) {
                drmHandleEvent(GetFD(drm), &evctx);
            }
        }
            
        if (FD_ISSET(0, &fds)) {
            printf("exit due to user-input\n");
        }
    }
    return 0;
}

drm_dev_t *creat_drm_device(const char *card)
{
    drm_dev_t * drm = (drm_dev_t *)malloc(sizeof(drm_dev_t));
    if (!drm) 
        return NULL;
    
    if (_opengDevice(drm, card))
    {
        printf("------open error---\n");
        return NULL;
    }

    if (_getConnector(drm))
    {
        printf("------getConnector---\n");
        return NULL;
    }

    drm->req = 1;

    return drm;
}