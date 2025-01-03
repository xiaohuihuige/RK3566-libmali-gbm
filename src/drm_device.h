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

typedef struct {
    int width;
    int height;
} Resolution;

typedef struct {
    // the display mode that we want to use
    drmModeModeInfo mode;
    // the connector ID that we want to use with this buffer
    uint32_t conn;
    // the crtc ID that we want to use with this connector
    uint32_t crtc;
    // the configuration of the crtc before we changed it. We use it so we can
    // restore the same mode when we exit.
    drmModeCrtc* saved_crtc;
} ModesetDev;

typedef struct {
    int req;
    int drmfd;
    ModesetDev *dev;
    drmEventContext evctx;
} drm_dev_t;

drm_dev_t *creat_drm_device(const char *card);
void drm_flush_wait(drm_dev_t * drm);

#endif