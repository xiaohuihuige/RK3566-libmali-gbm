#include "drm_device.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static int opengDevice(const char *card) 
{
    assert(card);
    int drmfd = open(card, O_RDWR | O_CLOEXEC);
    if (drmfd < 0) {
        printf("cannot open '%s':\n", card);
        return GLFW_FALS;
    }
    return drmfd;
}

static int findCrtc(int fd, drmModeRes* res, drmModeConnector* conn, uint32_t* crtc_out) 
{
    assert(res && conn && crtc_out);
    for (int i = 0; i < conn->count_encoders; ++i) {
        drmModeEncoder* enc = drmModeGetEncoder(fd, conn->encoders[i]);
        if (!enc) {
            printf("cannot retrieve encoder %u:%u (%d): %m\n", i, conn->encoders[i], errno);
            continue;
        }

        if (enc && enc->crtc_id) {
            uint32_t crtc = enc->crtc_id;
            if (crtc >= 0) {
                drmModeFreeEncoder(enc);
                *crtc_out = crtc;
                return GLFW_TRUE;
            }
        }
        drmModeFreeEncoder(enc);
    }

    printf("cannot find suitable CRTC for connector %u\n", conn->connector_id);
    return GLFW_FALS;
}

static ModesetDev *getConnector(int drmfd) 
{
    /* retrieve resources */
    drmModeRes* res_info = drmModeGetResources(drmfd);
    if (!res_info) {
        printf("cannot retrieve DRM resources (%d): %m\n", errno);
        return NULL;
    }

    /* iterate all connectors */
    for (int i = 0; i < res_info->count_connectors; ++i) {
        /* get information for each connector */
        drmModeConnector* conn = drmModeGetConnector(drmfd, res_info->connectors[i]);
        if (!conn) {
            printf("cannot retrieve DRM connector %u:%u (%d): %m\n", i,res_info->connectors[i], errno);
            continue;
        }

        /* check if a monitor is connected */
        if (conn->connection != DRM_MODE_CONNECTED) {
            drmModeFreeConnector(conn);
            printf("ignoring unused connector %u\n", conn->connector_id);
            continue;
        }

        /* check if there is at least one valid mode */
        if (!conn->count_modes) {
            drmModeFreeConnector(conn);
            printf("no valid mode for connector %u\n", conn->connector_id);
            continue;
        }

        ModesetDev *drm_dev = (ModesetDev *)malloc(sizeof(ModesetDev));
        if (!drm_dev) {
            drmModeFreeConnector(conn);
            printf("no valid mode for connector %u\n", conn->connector_id);
            return NULL;
        }

        drm_dev->conn = conn->connector_id;
        drm_dev->mode = conn->modes[0];

        /* find a crtc for this connector */
        if (!findCrtc(drmfd, res_info, conn, &drm_dev->crtc)) {
            printf("cannot setup device for connector %u:%u (%d): %m\n", i, res_info->connectors[i], errno);
            drmModeFreeConnector(conn);
            continue;
        }
        printf("drm->dev->crtc %d \n",drm_dev->crtc);
        drmModeFreeConnector(conn);
        return drm_dev;
    }

    /* free resources again */
    drmModeFreeResources(res_info);

    return NULL;
}

static int pageFlip(drm_dev_t *drm, uint32_t fb_id, void* user_data) {
    assert(drm);
    int ret = drmModePageFlip(drm->drmfd, drm->dev->crtc, fb_id, DRM_MODE_PAGE_FLIP_EVENT, user_data);
    if (ret) {
        printf("failed to queue page flip\n");
        return GLFW_FALS;
    }
    return GLFW_TRUE;
}

int modeSetCrtc(drm_dev_t *drm, uint32_t fb_id) 
{
    assert(drm);
    drm->dev->saved_crtc = drmModeGetCrtc(drm->drmfd, drm->dev->crtc);
    int ret = drmModeSetCrtc(drm->drmfd, drm->dev->crtc, fb_id, 0, 0, &drm->dev->conn, 1, &drm->dev->mode);
    if (ret) {
        printf( "cannot set CRTC for connector %u (%d): %m\n", drm->dev->conn, errno);
        return GLFW_FALS;
    }
    return GLFW_TRUE;
}

static void freeModeSetCrtc(drm_dev_t *drm)
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

int getHeight(drm_dev_t *drm)
{
    assert(drm);    
    return drm->dev->mode.hdisplay;
}

int getWidth(drm_dev_t *drm)
{
    assert(drm);    
    return drm->dev->mode.vdisplay;
}

int getDrmFd(drm_dev_t *drm)
{
    assert(drm);    
    return drm->drmfd;
}

static void onModesetPageFlipEvent(int fd, unsigned int frame, unsigned int sec, unsigned int usec, void* data) 
{
    assert(data);  
    didEGLPageFlip(sec, usec, data);
    printf("flip\n");
}

void drmFlushWait(drm_dev_t * drm, void *user_data, uint32_t fb_id)
{
    assert(drm);    

    struct pollfd pfd;
    pfd.fd = drm->drmfd;
    pfd.events = POLLIN | POLLPRI; 
    
    drmEventContext evctx = {};
    evctx.version = DRM_EVENT_CONTEXT_VERSION;
    evctx.page_flip_handler = onModesetPageFlipEvent;

    if (!pageFlip(drm, fb_id, user_data)) {
        printf("page flip error\n");
        return;
    }

    while(drm->req) {
        int ret;
        do {
            ret = poll(&pfd, 1, -1);
        } while(ret == -1 && errno == EINTR);

        if(ret > 0) {
            drmHandleEvent(drm->drmfd, &evctx);
        }
        else {
            printf("poll failed: %s\n", strerror(errno));
            return;
        }
    }
}

drm_dev_t *initDRMDevice(const char *card)
{
    drm_dev_t * drm_dev = (drm_dev_t *)malloc(sizeof(drm_dev_t));
    if (!drm_dev) 
        return NULL;

    do {
        drm_dev->drmfd = opengDevice(card);
        if (!drm_dev->drmfd) 
            break;

        drm_dev->dev = getConnector(drm_dev->drmfd);
        if (!drm_dev->dev) 
            break;

        drm_dev->req = 1;

        return drm_dev;
    } while (0);
 
    if (drm_dev) 
        free(drm_dev);
        
    return NULL;
}