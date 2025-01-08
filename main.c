#include <stdio.h>
#include "drm_device.h"
#include "egl_context.h"
#include "gles_demo.h"
#include <stdlib.h>
#include "usb_camera.h"

int main()
{
    drm_dev_t *drm = initDRMDevice("/dev/dri/card0");
    if (!drm) {
        printf("initDRMDevice error \n");
        return EXIT_FAILURE;
    }

    egl_window *egl = initEglWindow(getDrmFd(drm), getHeight(drm), getWidth(drm), drawPageFlip);
    if (!egl) {
        printf("create egl window error\n");
        return EXIT_FAILURE;
    }

    if (!initGLESDemo(getWidth(drm), getHeight(drm))) {
        printf("initGLESDemo error\n");
        return EXIT_FAILURE;
    }

    setGLESContext(egl, getGLESContext());

    if (!modeSetCrtc(drm, egl->framebuffers_[egl->front_buffer_].fb_id)) {
        printf("modeSetCrtcerror\n");
        return EXIT_FAILURE;
    }

    // usb_camera *usb_dev = create_usb_camera("/dev/video9", getWidth(drm), getHeight(drm));
    // if (!usb_dev) {
    //     printf("create_usb_camera error\n");
    //     return EXIT_FAILURE;
    // }

    // FrameBuf frame_buf;
    // while (1)
    // {
    //     if (!get_data_from_poll(usb_dev, &frame_buf))
    //     {
    //         printf("---error---\n");
    //     }   
    //     printf("---fps %d\n",frame_buf.length);
    // }
    

    Run(drm, egl, egl->framebuffers_[egl->front_buffer_].fb_id);

    return EXIT_SUCCESS;
}
