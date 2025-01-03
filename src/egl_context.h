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

struct EGLGlue {
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
    bool egl_sync_supported;
};


#endif