#include "egl_context.h"
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

void setGLESContext(egl_window *egl, void *gles_context)
{
    assert(egl);
    egl->gles_context_ = gles_context;
}

static void EGLSyncFence(EGLGlue *egl_context_) 
{
    if (egl_context_->egl_sync_supported) {
        EGLSyncKHR sync = egl_context_->CreateSyncKHR(egl_context_->display, EGL_SYNC_FENCE_KHR, NULL);
        glFlush();
        int ret = egl_context_->ClientWaitSyncKHR(egl_context_->display, sync, 0, EGL_FOREVER_KHR);
    } else {
        glFinish();
    }
}

static void printfEglFPS(unsigned long usec)
{
    static int num_frames = 0;
    static unsigned long lasttime = 0;
    static const size_t one_sec = 1000000;
    num_frames++;
    unsigned long elapsed = usec - lasttime;
    if (elapsed > one_sec) {
        printf("FPS: %4f \n", num_frames / ((double)elapsed / one_sec));
        num_frames = 0;
        lasttime = usec;
    }
}

void didEGLPageFlip(unsigned int sec, unsigned int usec, void *data) 
{
    assert(data);
    printfEglFPS(usec);
    egl_window *egl = (egl_window *)data;
    egl->page_flip_pending_ = 0;
    glBindFramebuffer(GL_FRAMEBUFFER, egl->framebuffers_[egl->front_buffer_].gl_fb);
    if (egl->callback_)
        egl->callback_(egl->gles_context_, egl->framebuffers_[egl->front_buffer_].gl_fb, sec * 1000000 + usec);
    EGLSyncFence(&egl->egl_context_);
}

static int glfwStringInExtensionString(const char* string, const char* extensions)
{
    const char* start = extensions;

    for (;;)
    {
        const char* where;
        const char* terminator;

        where = strstr(start, string);
        if (!where)
            return GLFW_FALS;

        terminator = where + strlen(string);
        if (where == start || *(where - 1) == ' ')
        {
            if (*terminator == ' ' || *terminator == '\0')
                break;
        }

        start = terminator;
    }

    return GLFW_TRUE;
}

static int initializeEGL(EGLGlue *egl_context_)
{
    assert(egl_context_);

    egl_context_->CreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    egl_context_->DestroyImageKHR =(PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
    egl_context_->EGLImageTargetTexture2DOES =(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
    egl_context_->CreateSyncKHR = (PFNEGLCREATESYNCKHRPROC)eglGetProcAddress("eglCreateSyncKHR");
    egl_context_->ClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)eglGetProcAddress("eglClientWaitSyncKHR");

    if (!egl_context_->CreateImageKHR || !egl_context_->DestroyImageKHR 
        || !egl_context_->EGLImageTargetTexture2DOES) {
        printf("eglGetProcAddress returned nullptr for a required extension entry point.\n");
        return GLFW_FALS;
    }

    if (egl_context_->CreateSyncKHR && egl_context_->ClientWaitSyncKHR) {
        egl_context_->egl_sync_supported = 1;
    } else {
        egl_context_->egl_sync_supported = 0;
    }

    EGLint major, minor = 0;
    egl_context_->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("Using display %p with EGL version %d.%d\n", egl_context_->display, major, minor);
        
    if (!eglInitialize(egl_context_->display, &major, &minor)) {
        printf("failed to initialize\n");
        return GLFW_FALS;
    }

    printf("Using display %p with EGL version %d.%d\n", egl_context_->display, major, minor);
    printf("EGL Version \"%s\"\n", eglQueryString(egl_context_->display, EGL_VERSION));
    printf("EGL Vendor \"%s\"\n", eglQueryString(egl_context_->display, EGL_VENDOR));

    if (!eglBindAPI(EGL_OPENGL_ES_API)) {
        printf("failed to bind api EGL_OPENGL_ES_API\n");
        return GLFW_FALS;
    }

    static const EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_DONT_CARE, EGL_NONE};
    EGLint num_config = 0;
    if (!eglChooseConfig(egl_context_->display, config_attribs, &egl_context_->config, 1, &num_config) || num_config != 1) {
        printf("failed to choose config: %d\n", num_config);
        return GLFW_FALS;
    }

    static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    egl_context_->context = eglCreateContext(egl_context_->display, egl_context_->config, EGL_NO_CONTEXT, context_attribs);
    if (egl_context_->context == NULL) {
        printf("failed to create context\n");
        return GLFW_FALS;
    }

    /* connect the context to the surface */
    if (!eglMakeCurrent(egl_context_->display, EGL_NO_SURFACE /* no default draw surface */, EGL_NO_SURFACE /* no default draw read */, egl_context_->context)) {
        printf("failed to make the OpenGL ES Context current: \n");
        return GLFW_FALS;
    }

    const char* egl_extensions = eglQueryString(egl_context_->display, EGL_EXTENSIONS);
    printf("EGL Extensions \"%s\"\n", egl_extensions);
    if (!glfwStringInExtensionString("EGL_KHR_image_base", egl_extensions)) {
        printf("EGL_KHR_image_base extension not supported\n");
        return GLFW_FALS;
    }
    if (!glfwStringInExtensionString("EGL_EXT_image_dma_buf_import", egl_extensions)) {
        printf("EGL_EXT_image_dma_buf_import extension not supported\n");
        return GLFW_FALS;
    }

    const char* gl_extensions = (const char*)glGetString(GL_EXTENSIONS);
    if (!glfwStringInExtensionString("GL_OES_EGL_image", gl_extensions)) {
        printf("GL_OES_EGL_image extension not supported\n");
        return GLFW_FALS;
    }

    return GLFW_TRUE;
}


static int createframebuffer(int height, int width, int drmfd, egl_window *egl, int number) 
{
    assert(egl);

    egl->framebuffers_[number].bo = gbm_bo_create(egl->gbm_, width, height, GBM_FORMAT_XRGB8888, GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
    if (!egl->framebuffers_[number].bo) {
        printf("failed to create a gbm buffer.\n");
        return GLFW_FALS;
    }

    egl->framebuffers_[number].fd = gbm_bo_get_fd(egl->framebuffers_[number].bo);
    if (egl->framebuffers_[number].fd < 0) {
        printf("failed to get fb for bo: %d", egl->framebuffers_[number].fd);
        return GLFW_FALS;
    }

    uint32_t handle = gbm_bo_get_handle(egl->framebuffers_[number].bo).u32;
    uint32_t stride = gbm_bo_get_stride(egl->framebuffers_[number].bo);
    uint32_t offset = 0;
    drmModeAddFB2(drmfd, width, height, GBM_FORMAT_XRGB8888, &handle, &stride, &offset, &egl->framebuffers_[number].fb_id, 0);
    if (!egl->framebuffers_[number].fb_id) {
        printf("failed to create framebuffers_[0] from buffer object.\n");
        return GLFW_FALS;
    }

    const EGLint khr_image_attrs[] = {EGL_DMA_BUF_PLANE0_FD_EXT,
                                        egl->framebuffers_[number].fd,
                                        EGL_WIDTH,
                                        width,
                                        EGL_HEIGHT,
                                        height,
                                        EGL_LINUX_DRM_FOURCC_EXT,
                                        GBM_FORMAT_XRGB8888,
                                        EGL_DMA_BUF_PLANE0_PITCH_EXT,
                                        (int)stride,
                                        EGL_DMA_BUF_PLANE0_OFFSET_EXT,
                                        (int)offset,
                                        EGL_NONE};

    egl->framebuffers_[number].image = egl->egl_context_.CreateImageKHR(egl->egl_context_.display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, khr_image_attrs);
    if (egl->framebuffers_[number].image == EGL_NO_IMAGE_KHR) {
        printf("failed to make image from buffer object: \n");
        return GLFW_FALS;
    }

    glGenTextures(1, &egl->framebuffers_[number].gl_tex);
    glBindTexture(GL_TEXTURE_2D, egl->framebuffers_[number].gl_tex);
    egl->egl_context_.EGLImageTargetTexture2DOES(GL_TEXTURE_2D, egl->framebuffers_[number].image);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &egl->framebuffers_[number].gl_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, egl->framebuffers_[number].gl_fb);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, egl->framebuffers_[number].gl_tex, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("failed framebuffer check for created target buffer: %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        glDeleteFramebuffers(1, &egl->framebuffers_[number].gl_fb);
        glDeleteTextures(1, &egl->framebuffers_[number].gl_tex);
        return GLFW_FALS;
    }
    printf("buffer fd %d,%d\n", egl->framebuffers_[number].fb_id, egl->framebuffers_[number].gl_fb);
    return GLFW_TRUE;
}

egl_window *initEglWindow(int drmfd, int height, int width, SwapBuffersCallback callback_)
{
    printf("egl window width: %d, height: %d\n",width, height);
    egl_window *egl = (egl_window *)malloc(sizeof(egl_window));
    if (!egl) 
        return NULL;

    do {
        egl->gbm_ = gbm_create_device(drmfd);
        if (!egl->gbm_) 
            break;

        if (!initializeEGL(&egl->egl_context_))  
            break;

        for (int i = 0; i < NUM_BUFFERS; i++) {
            if (!createframebuffer(height, width, drmfd, egl, i)) 
                break;
        }

        egl->front_buffer_ = 0;
        egl->callback_ = callback_;
        egl->page_flip_pending_ = 1;
        return egl;    
    } while(0);

    if (egl)
        free(egl);

    return NULL;
}

void destroyEglWindow(egl_window *egl)
{
    if (!egl)
        return;

    for (int i = 0, i < NUM_BUFFERS; i++)
    {
        glDeleteFramebuffers(1, &egl->framebuffers_[i].gl_fb);
        glDeleteTextures(1, &egl->framebuffers_[i].gl_tex);
        egl->egl_context_.DestroyImageKHR(egl_.display, egl->framebuffers_[i].image);
        drmModeRmFB(drm_->GetFD(), egl->framebuffers_[i].fb_id);
        close(egl->framebuffers_[i].fd);
        gbm_bo_destroy(egl->framebuffers_[i].bo);
    }

    eglDestroyContext(egl->egl_context_.display, egl->egl_context_.context);
    eglTerminate(egl->egl_context_.display);
    gbm_device_destroy(egl->gbm_);

    free(egl);
}