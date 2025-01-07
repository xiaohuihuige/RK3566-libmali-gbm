#ifndef __DRM_DEVICE_H__
#define __DRM_DEVICE_H__

#include <xf86drm.h>
#include <xf86drmMode.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <stdlib.h>
#include "egl_context.h"

typedef struct {
    drmModeModeInfo mode;     // the display mode that we want to use
    uint32_t conn;            // the connector ID that we want to use with this buffer
    uint32_t crtc;            // the crtc ID that we want to use with this connector
    drmModeCrtc* saved_crtc;  // the configuration of the crtc before we changed it. We use it so we can, restore the same mode when we exit.
} ModesetDev;

typedef struct {
    int req;
    int drmfd;
    ModesetDev *dev;
} drm_dev_t;

drm_dev_t *initDRMDevice(const char *card);
void drmFlushWait(drm_dev_t * drm, void *user_data, uint32_t fb_id);
int modeSetCrtc(drm_dev_t *drm, uint32_t fb_id);
int getWidth(drm_dev_t *drm);
int getHeight(drm_dev_t *drm);
int getDrmFd(drm_dev_t *drm);

#endif