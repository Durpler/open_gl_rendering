//
// Created by Durpler on 08/08/2021.
//

#include "OGLEWindow.h"
#include <iostream>

namespace ogle
{
    /*
     * Needs to be overriden by your applications app class
     */
    void * Interface::app;

    OgleWindow::OgleWindow() {
        m_Width = 800;
        m_Height = 600;
        m_Title = "TestWindow";
    }

    void OgleWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0,0,width, height);
        glClearColor(1,0,0,1);           //CLEAR WINDOW CONTENTS
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers((window));
    }

    OgleWindow::~OgleWindow() {
        // destroy this window
        glfwDestroyWindow((m_Window));
    }
}


