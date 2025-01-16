#ifndef __GELS_CAMERA_H__
#define __GELS_CAMERA_H__

#ifdef GLES_CAMERA_DEMO

#include <GLES2/gl2.h>
#include "egl_context.h"
#include "egl_stream_texture.h"

typedef struct  
{
   GLuint programObject;
   GLint samplerLoc;
   GLuint textureId;
   int width;
   int height;
   stream_texture_t *stream;
} gles_camera;

gles_camera *initDemo(egl_window *egl, int width, int height);
void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec);

#endif
#endif