#include <stdio.h>
#include "drm_device.h"

int main()
{
    const char* card = "/dev/dri/card0";
    drm_dev_t *drm = creat_drm_device(card);
    if (!drm) {
        printf("--------------errrorrr----------\n");
        return -1;
    }

    drm_flush_wait(drm);
}