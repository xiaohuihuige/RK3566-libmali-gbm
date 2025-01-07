#include "gles_demo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 

// void didPageFlip(GLuint gl_framebuffer, unsigned long usec) {
//     Draw(usec);

//     static int num_frames = 0;
//     static unsigned long lasttime = 0;
//     static const size_t one_sec = 1000000;
//     num_frames++;
//     unsigned long elapsed = usec - lasttime;
//     if (elapsed > one_sec) {
//         printf("FPS: %4f \n", num_frames / ((double)elapsed / one_sec));
//         num_frames = 0;
//         lasttime = usec;
//     }
// }

// void Draw(unsigned long usec) {

//     // 100% every 10 sec
//     static const int interval = 10000000.f;
//     float progress = 1.f * (usec % interval) / interval;
//     float red = pow(cos(M_PI * 2 * progress), 2) / 3;
//     float green = pow(cos(M_PI * 2 * (progress + 0.33)), 2) / 3;
//     float blue = pow(cos(M_PI * 2 * (progress + 0.66)), 2) / 3;
//     glClearColor(red, green, blue, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT);

//     // convert to 200ms precision, which covers 60FPS very enough.
//     int i = usec / 5000;
//     Matrix modelview;
//     modelview.Translate(0.0f, 0.0f, -8.0f);
//     modelview.Rotate(45.0f + (0.25f * i), 1.0f, 0.0f, 0.0f);
//     modelview.Rotate(45.0f - (0.5f * i), 0.0f, 1.0f, 0.0f);
//     modelview.Rotate(10.0f + (0.15f * i), 0.0f, 0.0f, 1.0f);

//     GLfloat aspect = (GLfloat)(display_size_.width) / (GLfloat)(display_size_.height);

//     Matrix projection;
//     float field_of_view = 35.f;
//     projection.Perspective(field_of_view, aspect, 6.f, 10.f);

//     Matrix modelviewprojection = modelview;
//     modelviewprojection.MatrixMultiply(projection);

//     glUniformMatrix4fv(modelviewmatrix_, 1, GL_FALSE, modelview.Data());
//     glUniformMatrix4fv(modelviewprojectionmatrix_, 1, GL_FALSE,
//                         modelviewprojection.Data());
//     float normal[9] = {};
//     modelview.Get3x3(&normal[0]);
//     glUniformMatrix3fv(normalmatrix_, 1, GL_FALSE, normal);

//     glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//     glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
//     glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
//     glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
//     glDrawArrays(GL_TRIANGLE_STRIP, 16, 4);
//     glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
// }

static int initializeGLProgram(gles_demo *demo) {
    static const char* vertex_shader_source =
        "uniform mat4 modelviewMatrix;      \n"
        "uniform mat4 modelviewprojectionMatrix;\n"
        "uniform mat3 normalMatrix;         \n"
        "                                   \n"
        "attribute vec4 in_position;        \n"
        "attribute vec3 in_normal;          \n"
        "attribute vec4 in_color;           \n"
        "\n"
        "vec4 lightSource = vec4(2.0, 2.0, 20.0, 0.0);\n"
        "                                   \n"
        "varying vec4 vVaryingColor;        \n"
        "                                   \n"
        "void main()                        \n"
        "{                                  \n"
        "    gl_Position = modelviewprojectionMatrix * in_position;\n"
        "    vec3 vEyeNormal = normalMatrix * in_normal;\n"
        "    vec4 vPosition4 = modelviewMatrix * in_position;\n"
        "    vec3 vPosition3 = vPosition4.xyz / vPosition4.w;\n"
        "    vec3 vLightDir = normalize(lightSource.xyz - vPosition3);\n"
        "    float diff = max(0.0, dot(vEyeNormal, vLightDir));\n"
        "    vVaryingColor = vec4(diff * in_color.rgb, 1.0);\n"
        "}                                  \n";

    static const char* fragment_shader_source =
        "precision mediump float;           \n"
        "                                   \n"
        "varying vec4 vVaryingColor;        \n"
        "                                   \n"
        "void main()                        \n"
        "{                                  \n"
        "    gl_FragColor = vVaryingColor;  \n"
        "}                                  \n";

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    GLint ret = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &ret);
    if (!ret) {
        printf("vertex shader compilation failed!:\n");
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &ret);
        if (ret > 1) {
            char* log = (char*)(malloc(ret));
            glGetShaderInfoLog(vertex_shader, ret, NULL, log);
            printf("%s\n", log);
            free(log);
        }
        return GLFW_FALS;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &ret);
    if (!ret) {
        printf("fragment shader compilation failed!:\n");
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &ret);
        if (ret > 1) {
            char* log = (char*)(malloc(ret));
            glGetShaderInfoLog(fragment_shader, ret, NULL, log);
            printf("%s\n", log);
            free(log);
        }
        return GLFW_FALS;
    }

    demo->program_ = glCreateProgram();

    glAttachShader(demo->program_, vertex_shader);
    glAttachShader(demo->program_, fragment_shader);

    glBindAttribLocation(demo->program_, 0, "in_position");
    glBindAttribLocation(demo->program_, 1, "in_normal");
    glBindAttribLocation(demo->program_, 2, "in_color");

    glLinkProgram(demo->program_);

    glGetProgramiv(demo->program_, GL_LINK_STATUS, &ret);
    if (!ret) {
        printf("program linking failed!:\n");
        glGetProgramiv(demo->program_, GL_INFO_LOG_LENGTH, &ret);
        if (ret > 1) {
             char* log = (char*)(malloc(ret));
            glGetProgramInfoLog(demo->program_, ret, NULL, log);
            printf("%s\n", log);
            free(log);
        }
        return GLFW_FALS;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    glUseProgram(demo->program_);
    return GLFW_TRUE;
}


static int initializeGL(gles_demo *demo, int width, int height) 
{
    static const GLfloat vVertices[] = {
        // front
        -1.0f, -1.0f, +1.0f,  // point blue
        +1.0f, -1.0f, +1.0f,  // point magenta
        -1.0f, +1.0f, +1.0f,  // point cyan
        +1.0f, +1.0f, +1.0f,  // point white
        // back
        +1.0f, -1.0f, -1.0f,  // point red
        -1.0f, -1.0f, -1.0f,  // point black
        +1.0f, +1.0f, -1.0f,  // point yellow
        -1.0f, +1.0f, -1.0f,  // point green
        // right
        +1.0f, -1.0f, +1.0f,  // point magenta
        +1.0f, -1.0f, -1.0f,  // point red
        +1.0f, +1.0f, +1.0f,  // point white
        +1.0f, +1.0f, -1.0f,  // point yellow
        // left
        -1.0f, -1.0f, -1.0f,  // point black
        -1.0f, -1.0f, +1.0f,  // point blue
        -1.0f, +1.0f, -1.0f,  // point green
        -1.0f, +1.0f, +1.0f,  // point cyan
        // top
        -1.0f, +1.0f, +1.0f,  // point cyan
        +1.0f, +1.0f, +1.0f,  // point white
        -1.0f, +1.0f, -1.0f,  // point green
        +1.0f, +1.0f, -1.0f,  // point yellow
        // bottom
        -1.0f, -1.0f, -1.0f,  // point black
        +1.0f, -1.0f, -1.0f,  // point red
        -1.0f, -1.0f, +1.0f,  // point blue
        +1.0f, -1.0f, +1.0f   // point magenta
    };

    static const GLfloat vColors[] = {
        // front
        0.0f, 0.0f, 1.0f,  // blue
        1.0f, 0.0f, 1.0f,  // magenta
        0.0f, 1.0f, 1.0f,  // cyan
        1.0f, 1.0f, 1.0f,  // white
        // back
        1.0f, 0.0f, 0.0f,  // red
        0.0f, 0.0f, 0.0f,  // black
        1.0f, 1.0f, 0.0f,  // yellow
        0.0f, 1.0f, 0.0f,  // green
        // right
        1.0f, 0.0f, 1.0f,  // magenta
        1.0f, 0.0f, 0.0f,  // red
        1.0f, 1.0f, 1.0f,  // white
        1.0f, 1.0f, 0.0f,  // yellow
        // left
        0.0f, 0.0f, 0.0f,  // black
        0.0f, 0.0f, 1.0f,  // blue
        0.0f, 1.0f, 0.0f,  // green
        0.0f, 1.0f, 1.0f,  // cyan
        // top
        0.0f, 1.0f, 1.0f,  // cyan
        1.0f, 1.0f, 1.0f,  // white
        0.0f, 1.0f, 0.0f,  // green
        1.0f, 1.0f, 0.0f,  // yellow
        // bottom
        0.0f, 0.0f, 0.0f,  // black
        1.0f, 0.0f, 0.0f,  // red
        0.0f, 0.0f, 1.0f,  // blue
        1.0f, 0.0f, 1.0f   // magentall
    };

    static const GLfloat vNormals[] = {
        // front
        +0.0f, +0.0f, +1.0f,  // forward
        +0.0f, +0.0f, +1.0f,  // forward
        +0.0f, +0.0f, +1.0f,  // forward
        +0.0f, +0.0f, +1.0f,  // forward
        // back
        +0.0f, +0.0f, -1.0f,  // backbard
        +0.0f, +0.0f, -1.0f,  // backbard
        +0.0f, +0.0f, -1.0f,  // backbard
        +0.0f, +0.0f, -1.0f,  // backbard
        // right
        +1.0f, +0.0f, +0.0f,  // right
        +1.0f, +0.0f, +0.0f,  // right
        +1.0f, +0.0f, +0.0f,  // right
        +1.0f, +0.0f, +0.0f,  // right
        // left
        -1.0f, +0.0f, +0.0f,  // left
        -1.0f, +0.0f, +0.0f,  // left
        -1.0f, +0.0f, +0.0f,  // left
        -1.0f, +0.0f, +0.0f,  // left
        // top
        +0.0f, +1.0f, +0.0f,  // up
        +0.0f, +1.0f, +0.0f,  // up
        +0.0f, +1.0f, +0.0f,  // up
        +0.0f, +1.0f, +0.0f,  // up
        // bottom
        +0.0f, -1.0f, +0.0f,  // down
        +0.0f, -1.0f, +0.0f,  // down
        +0.0f, -1.0f, +0.0f,  // down
        +0.0f, -1.0f, +0.0f   // down
    };

    if (!initializeGLProgram(demo))
        return GLFW_FALS;

    demo->modelviewmatrix_ = glGetUniformLocation(demo->program_, "modelviewMatrix");
    demo->modelviewprojectionmatrix_ = glGetUniformLocation(demo->program_, "modelviewprojectionMatrix");
    demo->normalmatrix_ = glGetUniformLocation(demo->program_, "normalMatrix");

    glViewport(0, 0, width, height);
    glEnable(GL_CULL_FACE);

    GLintptr positionsoffset = 0;
    GLintptr colorsoffset = sizeof(vVertices);
    GLintptr normalsoffset = sizeof(vVertices) + sizeof(vColors);
    glGenBuffers(1, &demo->vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, demo->vbo_);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vVertices) + sizeof(vColors) + sizeof(vNormals), 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, positionsoffset, sizeof(vVertices), &vVertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, colorsoffset, sizeof(vColors), &vColors[0]);
    glBufferSubData(GL_ARRAY_BUFFER, normalsoffset, sizeof(vNormals), &vNormals[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(positionsoffset));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(normalsoffset));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(colorsoffset));
    glEnableVertexAttribArray(2);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    return GLFW_TRUE;
}


const char* vertexShaderSource = R"(
    attribute vec4 position;
    void main() {
        gl_Position = position;
    }
)";

// 片段着色器源代码
const char* fragmentShaderSource = R"(
    precision mediump float;
    void main() {
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); // 红色
    }
)";

// 创建着色器
GLuint createShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
}

// 初始化 OpenGL ES 并绘制三角形
void initOpenGL(int width, int height) {
    // 创建着色器
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // 创建程序
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    //glUseProgram(program);

    // 定义三角形的顶点
    GLfloat vertices[] = {
        0.0f,  0.5f,  // 顶点 A
       -0.5f, -0.5f,  // 顶点 B
        0.5f, -0.5f   // 顶点 C
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 获取顶点位置属性的位置
    GLint posAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glViewport(0, 0, width, height);
    // // 清理
    // glDisableVertexAttribArray(posAttrib);
    // glDeleteBuffers(1, &VBO);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(program);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void didPageFlip(GLuint gl_framebuffer, unsigned long usec)
{
    // 绘制三角形
    printf("---start draw---\n");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

gles_demo *initGLESDemo(int width, int height)
{
    gles_demo *demo = (gles_demo *)malloc(sizeof(gles_demo));
    if (!demo) {
        return GLFW_FALS;
    }

    do {
        initOpenGL(width, height);
        // if (!initializeGL(demo, width, height)) {
        //     printf("initializeGL error\n");
        //     break;
        // }
        printf("opengles success \n");
        return demo;
    } while (0);
   
    if (demo)
        free(demo);

    return NULL;
}