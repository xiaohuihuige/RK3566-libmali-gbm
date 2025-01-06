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
    int width;
    int height;
} gles_demo;

int gles_demo_init(int width, int height);

#endif