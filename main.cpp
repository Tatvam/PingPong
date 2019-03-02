
#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<iostream>

using namespace std;

static unsigned int CompileShader(unsigned int type, const string& source){

    unsigned int id = glCreateShader(type);
    const char* src= source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
       int length;
       glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
       char* message = (char *)alloca(length * sizeof(char));
       glGetShaderInfoLog(id, length, &length, message);
       cout<<"Failed to compile " <<(type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<endl;
       cout<<message<<endl;

       glDeleteShader(id);

       return 0; 
    }

    return id;
}

static int CreateShader(const string& vertexShader, const string& fragmentShader){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



int main(){

    if( !glfwInit() ){
        fprintf( stderr , "Failed to initialize GLFW\n");
        return -1;
    }

    // set hints for the next call to glfwcreatewindow

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
    // make the context of the specified window current ont he calling thread
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if( glewInit() != GLEW_OK){
        fprintf(stderr,"Failed to initialize GLEW\n");
        return-1;
    }

    glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    
    GLuint VertexArrayID;
    // Important ?????
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    float positions[6] ={
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    // Create a buffer and store the data into GPU memory
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    // telling opengl the size of vertex and it properties
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    string vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

     string fragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    do{
        // rendering commands here
       // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);
        // check and call events and swap the buffers

        // Function swap the  front and back buffer of the specific window
        glfwSwapBuffers(window);
        // checks if any events are triggered (like keyboard or mouse)
        glfwPollEvents();
    }
    while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);
}