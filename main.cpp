
#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

using namespace glm;

int main(){

    if( !glfwInit() ){
        fprintf( stderr , "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES,4);// 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);// We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);// To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//We don't want the old OpenGL 

    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "PingPong", NULL, NULL);

    if(window==NULL){
        fprintf(stderr,"Failed to open GLFW window.\n");
        glfwTerminate();
        return-1;
    }

    glfwMakeContextCurrent(window);
    //glewExperimental = true;
    if( glewInit() != GLEW_OK){
        fprintf(stderr,"Failed to initialize GLEW\n");
        return-1;
    }

    glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    
    do{
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
}