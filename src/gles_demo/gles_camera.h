#ifndef __GELS_CAMERA_H__
#define __GELS_CAMERA_H__

#ifdef GLES_CAMERA_DEMO

#include <GLES2/gl2.h>
#include "egl_context.h"

typedef struct  
{
   GLuint programObject;
   GLint samplerLoc;
   GLuint textureId;
   int width;
   int height;
} gles_camera;

gles_camera *initDemo(int width, int height);
void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec);

#endif
#endif