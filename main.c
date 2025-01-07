#include <stdio.h>
#include "drm_device.h"
#include "egl_context.h"
#include "gles_demo.h"
#include <stdlib.h>

int main()
{
    drm_dev_t *drm = initDRMDevice("/dev/dri/card0");
    if (!drm) {
        printf("initDRMDevice error \n");
        return EXIT_FAILURE;
    }

    egl_window *egl = initEglWindow(getDrmFd(drm), getHeight(drm), getWidth(drm), didPageFlip);
    if (!egl) {
        printf("create egl window error\n");
        return EXIT_FAILURE;
    }

    gles_demo *demo = initGLESDemo(getWidth(drm), getHeight(drm));
    if (!demo) {
        printf("initGLESDemo error\n");
        return EXIT_FAILURE;
    }

    if (!modeSetCrtc(drm, egl->framebuffers_[egl->front_buffer_].fb_id)) {
        printf("modeSetCrtcerror\n");
        return EXIT_FAILURE;
    }

    drmFlushWait(drm, egl, egl->framebuffers_[egl->front_buffer_].fb_id);

    return EXIT_SUCCESS;
}
