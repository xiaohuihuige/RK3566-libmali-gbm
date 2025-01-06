#include <stdio.h>
#include "drm_device.h"
#include "egl_context.h"
#include "gles_demo.h"

int main()
{
    const char* card = "/dev/dri/card0";
    drm_dev_t *drm = creat_drm_device(card);
    if (!drm) {
        printf("--------------errrorrr----------\n");
        return -1;
    }

    egl_context *egl = init_egl(drm, NULL);
    if (!egl) {
        printf("--------------errrorrr----------\n");
        return -1;
    }
    printf("--------------ok----------\n");
    gles_demo_init(drm->dev->mode.hdisplay, drm->dev->mode.vdisplay);

    //pageFlip(drm, egl->framebuffers_[0].fb_id, NULL);

    Run(drm, egl->framebuffers_[0].fb_id, egl->framebuffers_[1].fb_id);
    //drm_flush_wait(drm);
}
