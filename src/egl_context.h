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
#include "drm_device.h"

#define NUM_BUFFERS 2
#define GLFW_TRUE   1
#define GLFW_FASE   0

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
    PFNEGLQUERYDEVICESEXTPROC   QueryDevicesEXT;
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
    struct gbm_device* gbm_;
    EGLGlue egl_;
    Framebuffer framebuffers_[NUM_BUFFERS];
    drm_dev_t *drm_;
    SwapBuffersCallback callback_;
} egl_context;


egl_context *init_egl(drm_dev_t *drm_, SwapBuffersCallback callback);

#endif