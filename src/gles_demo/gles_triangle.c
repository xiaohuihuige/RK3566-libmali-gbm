#include "gles_triangle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#ifdef GLES_TRIANGLE_DEMO 

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
gles_tringle *initDemo(int width, int height)
{
    // 创建着色器
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // 创建程序
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    //glUseProgram(program);
    //(-1，-1)

    //定义三角形的顶点
    GLfloat vertices[] = {
        -1.0f, -1.0f, // 左下角
        1.0f, -1.0f, // 右下角
        -1.0f, 1.0f,

        -1.0f, 1.0f,
        1.0f, -1.0f, // 右下
        1.0f, 1.0f  // 上中
    };


    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnable(GL_CULL_FACE);
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

    return NULL;
}

void didPageFlip(void *context, GLuint gl_framebuffer, unsigned long usec)
{
    // 绘制三角形
    printf("---start draw---\n");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

#endif