#ifndef __GLES_TRIANGLE_H__
#define __GLES_TRIANGLE_H__

#ifdef GLES_TRIANGLE_DEMO 

#include <GLES2/gl2.h>
#include "egl_context.h"

typedef struct  
{
    GLuint program_;
    GLint modelviewmatrix_;
    GLint modelviewprojectionmatrix_;
    GLint normalmatrix_;
    GLuint vbo_;
} gles_tringle;

gles_tringle *initDemo(int width, int height);
void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec);

#endif
#endif