#ifndef __GLES_CUBE_H__
#define __GLES_CUBE_H__

#ifdef GLES_CUBE_DEMO 
#include <GLES2/gl2.h>
#include "egl_context.h"

typedef struct  
{
    GLuint program_;
    GLint modelviewmatrix_;
    GLint modelviewprojectionmatrix_;
    GLint normalmatrix_;
    GLuint vbo_;
} gles_cube;

gles_cube *initDemo(int width, int height);
void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec);

#endif
#endif