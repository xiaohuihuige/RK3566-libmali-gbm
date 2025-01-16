#include "egl_stream_texture.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

void* Map(stream_texture_t *stream) 
{
    assert(stream->addr_ == NULL);
    size_t size = stream->stride_ * stream->height_;
    stream->addr_ = mmap(NULL, size, (PROT_READ | PROT_WRITE), MAP_SHARED, stream->Framebuffer_.fd,  0);
    if (stream->addr_ == MAP_FAILED)
        return NULL;

    return stream->addr_;
}

void Unmap(stream_texture_t *stream)
{
    assert(stream->addr_ != NULL);
    size_t size = stream->stride_ * stream->height_;
    munmap(stream->addr_, size);
    stream->addr_ = NULL;
}

GLuint GetTextureID(stream_texture_t *stream)
{ 
    assert(stream);
    return stream->Framebuffer_.gl_tex; 
}

static int create_stream_window(egl_window *egl, stream_texture_t *stream)
{
    assert(stream || egl);

    stream->Framebuffer_.bo = gbm_bo_create(egl->gbm_, stream->width_, stream->height_, GBM_FORMAT_ARGB8888, GBM_BO_USE_LINEAR);
    if (!stream->Framebuffer_.bo) {
        printf("failed to create a gbm buffer.\n");
        return GLFW_FALS;
    }

    stream->Framebuffer_.fd = gbm_bo_get_fd(stream->Framebuffer_.bo);
    if (stream->Framebuffer_.fd < 0) {
        printf("failed to get fb for bo: %d", stream->Framebuffer_.fd);
        return GLFW_FALS;
    }

    stream->stride_ = gbm_bo_get_stride(stream->Framebuffer_.bo);
    EGLint offset = 0;
    const EGLint khr_image_attrs[] = {EGL_DMA_BUF_PLANE0_FD_EXT,
                                        stream->Framebuffer_.fd,
                                        EGL_WIDTH,
                                        stream->width_,
                                        EGL_HEIGHT,
                                        stream->height_,
                                        EGL_LINUX_DRM_FOURCC_EXT,
                                        GBM_FORMAT_ARGB8888,
                                        EGL_DMA_BUF_PLANE0_PITCH_EXT,
                                        stream->stride_,
                                        EGL_DMA_BUF_PLANE0_OFFSET_EXT,
                                        offset,
                                        EGL_NONE};

    stream->Framebuffer_.image = egl_->CreateImageKHR(egl->egl_context_.display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, khr_image_attrs);
    if (stream->Framebuffer_.image == EGL_NO_IMAGE_KHR) {
        printf("failed to make image from buffer object\n");
        return GLFW_FALS;
    }

    glGenTextures(1, &stream->Framebuffer_.gl_tex);
    glBindTexture(GL_TEXTURE_2D, stream->Framebuffer_.gl_tex);

    egl->egl_context_.EGLImageTargetTexture2DOES(GL_TEXTURE_2D, stream->Framebuffer_.image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return GLFW_TRUE;
}

void destroyStreamTexture(egl_window *egl, stream_texture_t *stream)
{
    assert(stream || egl);

    glDeleteTextures(1, &stream->Framebuffer_.gl_tex);
    egl->egl_context_.DestroyImageKHR(egl_->display,  stream->Framebuffer_.image);
    close(stream->Framebuffer_.fd);
    gbm_bo_destroy(stream->Framebuffer_.bo);
}

stream_texture_t *createStreamTexture(egl_window *egl, int width, int height)
{
    assert(egl);

    stream_texture_t * stream = (stream_texture_t *)malloc(sizeof(stream_texture_t));
    if (!stream) 
        return NULL;
    
    stream->egl_context_ = egl->egl_context_;
    stream->width_  = width;
    stream->height_ = height;

    if (!create_stream_window(egl, stream))
        return NULL;

    return stream;
}


void updateStream()
{
    GLubyte pixels[4 * 3] =
    {
            255,   0,   0, // Red
            0, 255,   0, // Green
            0,   0, 255, // Blue
            255, 255,   0  // Yellow
    };

    // Use tightly packed data
    //glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

    // Load the texture
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels ); 
}