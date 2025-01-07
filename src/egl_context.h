#ifndef __EGL_CONTEXT_H__
#define __EGL_CONTEXT_H__

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <gbm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

#define NUM_BUFFERS 2
#define GLFW_TRUE   1
#define GLFW_FALS   0

typedef void (*SwapBuffersCallback)(GLuint, unsigned long);

typedef struct {
    EGLDisplay display;
    EGLConfig config;
    EGLContext context;

    // Names are the original gl/egl function names with the prefix chopped off.
    PFNEGLCREATEIMAGEKHRPROC CreateImageKHR;
    PFNEGLDESTROYIMAGEKHRPROC DestroyImageKHR;
    PFNGLEGLIMAGETARGETTEXTURE2DOESPROC EGLImageTargetTexture2DOES;
    PFNEGLCREATESYNCKHRPROC CreateSyncKHR;
    PFNEGLCLIENTWAITSYNCKHRPROC ClientWaitSyncKHR;
    int egl_sync_supported;
} EGLGlue;

typedef struct {
    struct gbm_bo* bo;
    int fd;
    uint32_t fb_id;
    EGLImageKHR image;
    GLuint gl_tex;
    GLuint gl_fb;
} Framebuffer;

typedef struct 
{
    unsigned int front_buffer_;
    struct gbm_device* gbm_;
    EGLGlue egl_context_;
    Framebuffer framebuffers_[NUM_BUFFERS];
    SwapBuffersCallback callback_;
} egl_window;

egl_window *initEglWindow(int drmfd, int height, int width, SwapBuffersCallback callback_);
void didEGLPageFlip(unsigned int sec, unsigned int usec, void *data);

#endif