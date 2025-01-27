#ifndef __GLES_DEMO_H__
#define __GLES_DEMO_H__

#include <GLES2/gl2.h>
#include "egl_context.h"

typedef void *(*initGLESDmoe)(egl_window, int, int);

typedef struct  
{
    initGLESDmoe demoCallback_;
    SwapBuffersCallback didPageFlip_;
    void *context;
} gles_demo;

int initGLESDemo(egl_window *egl, int width, int height);
void drawPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec);
void *getGLESContext(void);

#endif