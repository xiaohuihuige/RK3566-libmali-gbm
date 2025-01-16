#include "gles_camera.h"
#include "stb_image.h"
#include <stdlib.h>
#include "esUtil.h"
#include <assert.h>

#ifdef GLES_CAMERA_DEMO

GLuint CreateSimpleTexture2D( )
{

   // 2x2 Image, 3 bytes per pixel (R, G, B)
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

//    // Set the filtering mode
//    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
//    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}

///
// Initialize the shader and program object
//
int Init(gles_camera *camera, int width, int height)
{
    char vShaderStr[] =
      "#version 300 es                            \n"
      "layout(location = 0) in vec4 a_position;   \n"
      "layout(location = 1) in vec2 a_texCoord;   \n"
      "out vec2 v_texCoord;                       \n"
      "void main()                                \n"
      "{                                          \n"
      "   gl_Position = a_position;               \n"
      "   v_texCoord = a_texCoord;                \n"
      "}                                          \n";

    char fShaderStr[] =
        "#version 300 es                                     \n"
        "precision mediump float;                            \n"
        "in vec2 v_texCoord;                                 \n"
        "layout(location = 0) out vec4 outColor;             \n"
        "uniform sampler2D s_texture;                        \n"
        "void main()                                         \n"
        "{                                                   \n"
        "  outColor = texture( s_texture, v_texCoord );      \n"
        "}                                                   \n";

    // Load the shaders and get a linked program object
    camera->programObject = esLoadProgram ( vShaderStr, fShaderStr );
    glUseProgram (camera->programObject);
    // Get the sampler location
    camera->samplerLoc = glGetUniformLocation ( camera->programObject, "s_texture" );

    // Load the texture
    CreateSimpleTexture2D ();


       GLfloat vVertices[] = { -0.5f,  0.5f, 0.0f,  // Position 0
                            0.0f,  0.0f,        // TexCoord 0 
                           -0.5f, -0.5f, 0.0f,  // Position 1
                            0.0f,  1.0f,        // TexCoord 1
                            0.5f, -0.5f, 0.0f,  // Position 2
                            1.0f,  1.0f,        // TexCoord 2
                            0.5f,  0.5f, 0.0f,  // Position 3
                            1.0f,  0.0f         // TexCoord 3
                         };

    // Set the viewport
    glViewport ( 0, 0, camera->width, camera->height );

    // Load the vertex position
    glVertexAttribPointer ( 0, 3, GL_FLOAT,GL_FALSE, 5 * sizeof ( GLfloat ), vVertices );
    // Load the texture coordinate
    glVertexAttribPointer ( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof ( GLfloat ), &vVertices[3] );

    glEnableVertexAttribArray ( 0 );
    glEnableVertexAttribArray ( 1 );

    // Set the sampler texture unit to 0
    glUniform1i ( camera->samplerLoc, 0 );

    glClearColor ( 1.0f, 1.0f, 1.0f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT);
    return GLFW_TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void Draw(gles_camera *camera)
{
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
     // Clear the color buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    CreateSimpleTexture2D( );
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, GetTextureID(camera->stream));
    glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices );
}

///
// Cleanup
//
void ShutDown(gles_camera *camera)
{
   // Delete texture object
   glDeleteTextures(1, &camera->textureId);

   // Delete program object
   glDeleteProgram(camera->programObject);
}

gles_camera *initDemo(egl_window *egl, int width, int height)
{
    gles_camera* camera = (gles_camera*)malloc(sizeof(gles_camera));
    if (!camera) {
        return NULL;
    }

    if (!Init(camera, width, height))
    {
        return NULL;
    }

    camera->stream = createStreamTexture(egl, width, height);

    return camera;
}

void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec)
{
    assert(context);
    gles_camera *camera = (gles_camera *)context;
    Draw(camera);
}

#endif