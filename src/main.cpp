#include "main.h"
#include "Tile.h"
// #include "timer.h"


Tile* player;
Tile* player2;

unsigned int shader;

struct ShaderProgramSource{
    string VertexSource;
    string FragmentSource;
};

static ShaderProgramSource ParseShader(const string& filepath){

    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1 
    };

    string line;
    stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream,line)){
        if(line.find("#shader")!=string::npos){
            if(line.find("vertex")!=string::npos){
                type = ShaderType::VERTEX;
            }else if(line.find("fragment")!=string::npos){
                type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int)type] <<line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

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

void draw(){

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader);
    player->draw();
    player2->draw();
    //glDrawArrays(GL_TRIANGLES,0,6);
}

void key_input(GLFWwindow* window){
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);

    if(up == GLFW_PRESS){
        if((player->y+player->length) < .850000)
        player->y = player->y + 0.0005;
    }else if(down == GLFW_PRESS){
        if(player->y > -1.0000000)
        player->y = player->y - 0.0005;
    }
    if(w == GLFW_PRESS){
        if((player2->y+player2->length) < .850000)
        player2->y = player2->y + 0.0005;
    }else if(s == GLFW_PRESS){
        if(player2->y > -1.0000000)
        player2->y = player2->y - 0.0005;
    }
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
        return -1;
    }
    // make the context of the specified window current ont he calling thread
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if( glewInit() != GLEW_OK){
        fprintf(stderr,"Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);
    

    player = new Tile(-1.0, 0.0, .30, .05);
    player2 = new Tile(.95, 0.0, .30, .05);

    ShaderProgramSource source = ParseShader("../res/shaders/Shader.shader");
   // cout<<source.VertexSource<<endl;
   // cout<<source.FragmentSource<<endl;
    shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    do{
        // rendering commands here
       // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        draw();
        // check and call events and swap the buffers
        // Function swap the  front and back buffer of the specific window
        glfwSwapBuffers(window);
        key_input(window);

        draw();

        // checks if any events are triggered (like keyboard or mouse)
        glfwPollEvents();
    }
    while(glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS && glfwWindowShouldClose(window)==0);

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}