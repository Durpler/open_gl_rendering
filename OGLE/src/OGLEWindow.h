//
// Created by Durpler on 08/08/2021.
//

#ifndef OGLE_OGLEWINDOW_H
#define OGLE_OGLEWINDOW_H

#include "CommonHeaders.h"
// std
#include <string>
namespace ogle
{

    struct Interface {

        static void * app; // <-- an unknown application to be defined later

        template<class APPLICATION>
        static void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods){
            ((APPLICATION*)(app))->onKeyDown(key,action);
        }

        template<class APPLICATION>
        static void OnMouseMove(GLFWwindow* window, double x, double y){
            ((APPLICATION*)(app))->onMouseMove(x,y);
        }

        template<class APPLICATION>
        static void OnMouseDown(GLFWwindow* window, int button, int action, int mods){
            ((APPLICATION*)(app))->onMouseDown(button,action);
        }

    };



    class OgleWindow
    {
    public: 
        OgleWindow();
        ~OgleWindow();
        //use a template class application to get global definitions like callbacks, size, etc.
        template<class APPLICATION>
        void create(APPLICATION* app, int width, int height) {
            ogle::Interface::app = app;
            m_Width = width;
            m_Height = height;

            // create actual glfwWindow
            m_Window = glfwCreateWindow(width, height, "TestTitle", nullptr, nullptr);
            if(!m_Window)
            {
                std::cout << "Could not create glfwWindow" << std::endl;
                return;
            }
            glfwMakeContextCurrent(m_Window);
            //glfwSwapInterval(1);

            //register callbacks for keyboard and mouse
            glfwSetKeyCallback(m_Window, Interface::OnKeyDown<APPLICATION>);
            glfwSetCursorPosCallback(m_Window, Interface::OnMouseMove<APPLICATION> );
            glfwSetMouseButtonCallback(m_Window, Interface::OnMouseDown<APPLICATION> );
            glfwSetFramebufferSizeCallback(m_Window, OgleWindow::framebuffer_size_callback);

            return;
        }

        inline bool shouldClose() { return glfwWindowShouldClose(m_Window); }
        inline GLFWwindow* getWindow() {return m_Window; }
        inline void swapBuffers(){      glfwSwapBuffers(m_Window);}

        //Get the Current framebuffer Size in pixels and Set the Viewport to it
        inline void setViewport(){
            glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
            glViewport(0,0,m_Width,m_Height);
        }
        // this allows us to grab the callbacks from the application
        Interface m_Interface;

    private:
        int m_Width = 800;
        int m_Height = 600;

        std::string m_Title;

        GLFWwindow * m_Window;

       static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    };
}


#endif //OGLE_LIBRARY_OGLEWINDOW_H
