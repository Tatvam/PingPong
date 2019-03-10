#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<sys/socket.h>
#include<sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>

using namespace std;

struct color_t {
    int r;
    int g;
    int b;
};

struct VAO *create2DObject(GLenum primitive_mode, int numVertices, const float *vertex_buffer_data);
// struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
// struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void draw2DObject(struct VAO *vao, GLenum mode, int numVertices, const float *vertex_buffer);

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    int    NumVertices;
};
typedef struct VAO VAO;
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_GROUND_1;
extern const color_t COLOR_LOG;
extern const color_t COLOR_HONEY;
extern const color_t COLOR_BLUE;

#endif