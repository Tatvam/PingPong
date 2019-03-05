#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "main.h"

using namespace std;

struct VAO* create2DObject(GLenum mode, int numVertices, const float* vertex_buffer){

    struct VAO* vao = new struct VAO;
    vao->NumVertices = numVertices;

    glGenVertexArrays(1, &(vao->VertexArrayID));
    glBindVertexArray(vao->VertexArrayID);

    glGenBuffers(1,&(vao->VertexBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);
    // for(int i = 0;i<12;i++){
    //     printf("%f\n",vertex_buffer[i]);
    // }
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(float), vertex_buffer, GL_STREAM_DRAW);

    // telling opengl the size of vertex and it properties
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    return vao;
}

void draw2DObject(struct VAO* vao, GLenum mode, int numVertices, const float* vertex_buffer){

    glBindVertexArray(vao->VertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, vao->VertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, numVertices*sizeof(float), vertex_buffer);

    glDrawArrays(mode, 0, 6);

}