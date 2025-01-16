#ifndef __EGL_STREAM_TEXTURE_H__
#define __EGL_STREAM_TEXTURE_H__

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <gbm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include "egl_context.h"

typedef struct {
    EGLGlue* egl_context_;
    void* addr_;
    int width_;
    int height_;
    int stride_;
    Framebuffer Framebuffer_;
} stream_texture_t;

stream_texture_t *createStreamTexture(egl_window *egl, int width, int height);
void destroyStreamTexture(egl_window *egl, stream_texture_t *stream);
GLuint GetTextureID(stream_texture_t *stream);
void* Map(stream_texture_t *stream);
void Unmap(stream_texture_t *stream);

#endif