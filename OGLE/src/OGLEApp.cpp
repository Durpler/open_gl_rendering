//
// Created by Durpler on 08/08/2021.
//
#include "OGLEApp.h"

// std
#include <iostream>
namespace ogle
{

    OgleApp::OgleApp() {
        m_Width = 800;
        m_Height = 600;
    }

    OgleApp::~OgleApp() {
        glfwTerminate();
    }

    void OgleApp::start() {
        while(!m_AppWindow.shouldClose())
        {
            m_AppWindow.setViewport();
            glClearColor(.2,.2,.2,1);
            glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            onDraw();

            m_AppWindow.swapBuffers();      //<-- SWAP BUFFERS
            glfwPollEvents();           //<-- LISTEN FOR WINDOW EVENTS
        }
    }

    bool OgleApp::initialize(int width, int height) {
        m_Width = width;
        m_Height = height;
        //TODO:: add proper logging
        if(!glfwInit())
        {
            std::cout << "Could not initialize GLFW" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



        m_AppWindow.create(this, m_Width, m_Height);
        // initialize glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;

        std::cout << "GLSL Version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glLineWidth(3);               //<-- Thicken lines so we can see 'em clearly
        return true;
    }
}
