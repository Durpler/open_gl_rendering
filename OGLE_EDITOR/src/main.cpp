//
// Created by Durpler on 08/08/2021.
//
#include "OGLEApp.h"
#include <iostream>
#include <vector>

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

/*-----------------------------------------------------------------------------
 *  SOME SHADER CODE
 *-----------------------------------------------------------------------------*/
const char * vert = GLSL(460,
                         in vec4 position;
                                 //note: "attribute" should be changed to "in" on versions 130 and above

                                 void main(){
                                     gl_Position = position;
                                 }
                    );

const char * frag = GLSL(460,
                         void main(){
                             gl_FragColor = vec4(1.0,1.0,1.0,1.0);
                         }
                    );

// Shader utils
// Check for compilation errors
void shaderCompilerCheck(GLuint ID)
{
    GLint comp;
    glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);
    // check for compilation result
    if(comp == GL_FALSE)
    {
        // output error-log, in case shader compilation failed
        std::cout << "Shader compilation failed" << std::endl;
        GLchar messages[256];
        glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages << std::endl;
    }
}

// check for shader link errors
void shaderLinkCheck(GLuint ID)
{
    GLint linkStatus;
    GLint validateStatus;
    glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);
    // query link status and if false output error-log
    if(linkStatus == GL_FALSE)
    {
        std::cout << "Shader linking failed" << std::endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages << std::endl;
    }

    glValidateProgram(ID);
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

    if(linkStatus == GL_FALSE)
    {
        std::cout << "Shader validation failed" << std::endl;
        GLchar messages[256];
        glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
        std::cout << messages << std::endl;
    }
}

struct vec2 {
    vec2(float _x=0, float _y=0) : x(_x), y(_y) {}
    float x,y;
};

class MyApp : public ogle::OgleApp
{
public:
    MyApp() : ogle::OgleApp(){};

    //cointainer for vertices
    std::vector<vec2> triangle;

    // shader ID
    GLuint sID;
    //vertex attribute ID
    GLuint positionID;
    //A buffer ID
    GLuint bufferID;
    //A Vertex ID
    GLuint arrayID;

    void onDraw() override
    {
        glUseProgram(sID);
        glBindVertexArray(arrayID);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);
    }

    void onMouseMove(int x, int y) override{
        std::cout << x << " " << y << std::endl;
    }
    void onMouseDown(int button, int action) override{
        if (action==GLFW_PRESS) std::cout << "mouse pressed" <<std::endl;
        if (action==GLFW_RELEASE) std::cout << "mouse released" <<std::endl;
    }
    void onKeyDown(int key, int action) override{
        std::cout << (unsigned char)key << std::endl;
    }

    bool setUp()
    {
        triangle.push_back(vec2(-1, -0.5f));
        triangle.push_back(vec2(0,1));
        triangle.push_back(vec2(1,-0.5f));

        //1.create the shader program
        sID = glCreateProgram();
        GLuint vID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

        //2. Load Shader Source Code
        glShaderSource(vID, 1, &vert, NULL);
        glShaderSource(fID, 1, &frag, NULL);

        //3. compile shaders
        glCompileShader(vID);
        glCompileShader(fID);

        //4. Check for errors in compilation
        shaderCompilerCheck(vID);
        shaderCompilerCheck(fID);

        //5. attach shaders to program
        glAttachShader(sID, vID);
        glAttachShader(sID, fID);

        //6. Link program
        glLinkProgram(sID);

        // 7. Check  for linking errors
        shaderLinkCheck(sID);

        //8. use program
        glUseProgram(sID);

        //Get locations of variables in the program
        positionID = glGetAttribLocation(sID, "position");

        //9. Unbind Program;
        glUseProgram(0);

        //create the vertex array object
        glGenVertexArrays(1, &arrayID);
        glBindVertexArray(arrayID);

        // create the vertex buffer object
        glGenBuffers(1, &bufferID);
        glBindBuffer(GL_ARRAY_BUFFER,bufferID);
        glBufferData(GL_ARRAY_BUFFER, triangle.size() * sizeof(vec2), triangle.data(), GL_STATIC_DRAW);

        // enable vertex attributes
        glEnableVertexAttribArray(positionID);

        // Tell OpenGL how to handle the buffer of data
        //                      attrib    num   type     normalize   stride   offset
        glVertexAttribPointer( positionID, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0 );

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        return true;
    }
};


int main()
{
    MyApp myApp;
    ogle::Interface::app = &myApp;
    myApp.initialize(1280,720);
    myApp.setUp();
    myApp.start();
    return 0;
}
