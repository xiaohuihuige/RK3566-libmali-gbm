#include "gles_demo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include <assert.h>
#ifdef GLES_TRIANGLE_DEMO
#include "gles_triangle.h"
#elif GLES_CAMERA_DEMO
#include "gles_camera.h"
#endif

static gles_demo *global_demo= NULL;

int initGLESDemo(int width, int height)
{
    printf("GLESDemo width: %d, height: %d\n",width, height);
    global_demo = (gles_demo *)malloc(sizeof(gles_demo));
    if (!global_demo) {
        return GLFW_FALS;
    }

    global_demo->demoCallback_ = initDemo;
    global_demo->didPageFlip_  = didPageFlip;

    if (global_demo->demoCallback_)
        global_demo->context = global_demo->demoCallback_(width, height);

    return GLFW_TRUE;
}

void *getGLESContext(void)
{
    assert(global_demo);
    return global_demo->context;
}

void drawPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec)
{
    if (global_demo && global_demo->didPageFlip_)
        global_demo->didPageFlip_(context, gl_framebuffer, usec);
}