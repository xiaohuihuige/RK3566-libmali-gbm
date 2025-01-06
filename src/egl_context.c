#include "egl_context.h"

int _glfwStringInExtensionString(const char* string, const char* extensions)
{
    const char* start = extensions;

    for (;;)
    {
        const char* where;
        const char* terminator;

        where = strstr(start, string);
        if (!where)
            return GLFW_FASE;

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

int InitializeEGL(egl_context *egl)
{
    //egl->egl_.QueryDevicesEXT =(PFNEGLQUERYDEVICESEXTPROC)eglGetProcAddress("eglQueryDevicesEXT");
    egl->egl_.CreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
    egl->egl_.DestroyImageKHR =(PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
    egl->egl_.EGLImageTargetTexture2DOES =(PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
    egl->egl_.CreateSyncKHR = (PFNEGLCREATESYNCKHRPROC)eglGetProcAddress("eglCreateSyncKHR");
    egl->egl_.ClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)eglGetProcAddress("eglClientWaitSyncKHR");

    if (!egl->egl_.CreateImageKHR || !egl->egl_.DestroyImageKHR 
        || !egl->egl_.EGLImageTargetTexture2DOES) {
        fprintf(stderr, "eglGetProcAddress returned nullptr for a required extension entry " "point. %p\n", egl->egl_.QueryDevicesEXT);
        return GLFW_FASE;
    }

    if (egl->egl_.CreateSyncKHR && egl->egl_.ClientWaitSyncKHR) {
        egl->egl_.egl_sync_supported = 1;
    } else {
        egl->egl_.egl_sync_supported = 0;
    }

    EGLint major, minor = 0;
    egl->egl_.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    printf("Using display %p with EGL version %d.%d\n", egl->egl_.display, major, minor);
        
    if (!eglInitialize(egl->egl_.display, &major, &minor)) {
        fprintf(stderr, "failed to initialize\n");
        return GLFW_FASE;
    }

    printf("Using display %p with EGL version %d.%d\n", egl->egl_.display, major, minor);
    printf("EGL Version \"%s\"\n", eglQueryString(egl->egl_.display, EGL_VERSION));
    printf("EGL Vendor \"%s\"\n", eglQueryString(egl->egl_.display, EGL_VENDOR));

    if (!eglBindAPI(EGL_OPENGL_ES_API)) {
        fprintf(stderr, "failed to bind api EGL_OPENGL_ES_API\n");
        return GLFW_FASE;
    }

    static const EGLint config_attribs[] = {EGL_SURFACE_TYPE, EGL_DONT_CARE, EGL_NONE};
    EGLint num_config = 0;
    if (!eglChooseConfig(egl->egl_.display, config_attribs, &egl->egl_.config, 1, &num_config) || num_config != 1) {
        fprintf(stderr, "failed to choose config: %d\n", num_config);
        return GLFW_FASE;
    }

    static const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
    egl->egl_.context = eglCreateContext(egl->egl_.display, egl->egl_.config, EGL_NO_CONTEXT, context_attribs);
    if (egl->egl_.context == NULL) {
        fprintf(stderr, "failed to create context\n");
        return GLFW_FASE;
    }

    /* connect the context to the surface */
    if (!eglMakeCurrent( egl->egl_.display, EGL_NO_SURFACE /* no default draw surface */, EGL_NO_SURFACE /* no default draw read */, egl->egl_.context)) {
        fprintf(stderr, "failed to make the OpenGL ES Context current: \n");
        return GLFW_FASE;
    }

    const char* egl_extensions = eglQueryString(egl->egl_.display, EGL_EXTENSIONS);
    printf("EGL Extensions \"%s\"\n", egl_extensions);
    if (!_glfwStringInExtensionString("EGL_KHR_image_base", egl_extensions)) {
        fprintf(stderr, "EGL_KHR_image_base extension not supported\n");
        return GLFW_FASE;
    }
    if (!_glfwStringInExtensionString("EGL_EXT_image_dma_buf_import", egl_extensions)) {
        fprintf(stderr, "EGL_EXT_image_dma_buf_import extension not supported\n");
        return GLFW_FASE;
    }

    const char* gl_extensions = (const char*)glGetString(GL_EXTENSIONS);
    if (!_glfwStringInExtensionString("GL_OES_EGL_image", gl_extensions)) {
        fprintf(stderr, "GL_OES_EGL_image extension not supported\n");
        return GLFW_FASE;
    }

    return GLFW_TRUE;
}


 
int Createframebuffer(int width, int height, int drmfd, struct gbm_device* gbm_, Framebuffer *buffer, EGLGlue *egl_) 
{
    printf("----width %d, height %d-\n", width, height);
    buffer->bo = gbm_bo_create(gbm_, width, height, GBM_FORMAT_XRGB8888, GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
    if (!buffer->bo) {
        fprintf(stderr, "failed to create a gbm buffer.\n");
        return GLFW_FASE;
    }

    buffer->fd = gbm_bo_get_fd(buffer->bo);
    if (buffer->fd < 0) {
        fprintf(stderr, "failed to get fb for bo: %d", buffer->fd);
        return GLFW_FASE;
    }

    uint32_t handle = gbm_bo_get_handle(buffer->bo).u32;
    uint32_t stride = gbm_bo_get_stride(buffer->bo);
    uint32_t offset = 0;
    drmModeAddFB2(drmfd, width, height, GBM_FORMAT_XRGB8888, &handle, &stride, &offset, &buffer->fb_id, 0);
    if (!buffer->fb_id) {
        fprintf(stderr, "failed to create framebuffers_[0] from buffer object.\n");
        return GLFW_FASE;
    }

    const EGLint khr_image_attrs[] = {EGL_DMA_BUF_PLANE0_FD_EXT,
                                        buffer->fd,
                                        EGL_WIDTH,
                                        width,
                                        EGL_HEIGHT,
                                        height,
                                        EGL_LINUX_DRM_FOURCC_EXT,
                                        GBM_FORMAT_XRGB8888,
                                        EGL_DMA_BUF_PLANE0_PITCH_EXT,
                                        stride,
                                        EGL_DMA_BUF_PLANE0_OFFSET_EXT,
                                        offset,
                                        EGL_NONE};

    buffer->image = egl_->CreateImageKHR(egl_->display, EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, NULL, khr_image_attrs);
    if (buffer->image == EGL_NO_IMAGE_KHR) {
        fprintf(stderr, "failed to make image from buffer object: \n");
        return GLFW_FASE;
    }

    glGenTextures(1, &buffer->gl_tex);
    glBindTexture(GL_TEXTURE_2D, buffer->gl_tex);
    egl_->EGLImageTargetTexture2DOES(GL_TEXTURE_2D, buffer->image);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &buffer->gl_fb);
    glBindFramebuffer(GL_FRAMEBUFFER, buffer->gl_fb);


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer->gl_tex, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "failed framebuffer check for created target buffer: %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        glDeleteFramebuffers(1, &buffer->gl_fb);
        glDeleteTextures(1, &buffer->gl_tex);
        return GLFW_FASE;
    }
    printf("buffer fd %d \n", buffer->fb_id);
    return GLFW_TRUE;
}


egl_context *init_egl(drm_dev_t *drm_, SwapBuffersCallback callback)
{
    egl_context *egl = (egl_context *)malloc(sizeof(egl_context));
    if (!egl) {
        return NULL;
    }

    egl->gbm_ = gbm_create_device(GetFD(drm_));
    if (!egl->gbm_) {
        return NULL;
    }

    if (!InitializeEGL(egl)) {
        printf("create buffer errror\n");
        return NULL;
    }

    for (int i = 0; i < 2; i++)
    {
        Framebuffer buffer;
        if (GLFW_FASE == Createframebuffer(drm_->dev->mode.hdisplay, drm_->dev->mode.vdisplay, drm_->drmfd, egl->gbm_, &buffer, &egl->egl_)) {
            printf("create buffer errror\n");
            return NULL;
        }
        egl->framebuffers_[i].bo = buffer.bo;
        egl->framebuffers_[i].fd = buffer.fd;
        egl->framebuffers_[i].fb_id = buffer.fb_id;
        egl->framebuffers_[i].image = buffer.image;
        egl->framebuffers_[i].gl_tex = buffer.gl_tex;
        egl->framebuffers_[i].gl_fb = buffer.gl_fb;
    }

    printf("------------%d,%d\n", egl->framebuffers_[0].fb_id, egl->framebuffers_[1].fb_id);
    modeSetCrtc(drm_, egl->framebuffers_[0].fb_id); 

    return egl;
}