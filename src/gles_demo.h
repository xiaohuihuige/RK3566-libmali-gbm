#ifndef __GLES_DEMO_H__
#define __GLES_DEMO_H__

#include <GLES2/gl2.h>
#include "egl_context.h"

typedef struct  
{
    GLuint program_;
    GLint modelviewmatrix_;
    GLint modelviewprojectionmatrix_;
    GLint normalmatrix_;
    GLuint vbo_;
} gles_demo;

gles_demo *initGLESDemo(int width, int height);
void didPageFlip(GLuint gl_framebuffer, unsigned long usec);

#endif