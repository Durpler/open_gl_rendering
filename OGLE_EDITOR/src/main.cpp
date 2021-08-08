//
// Created by Durpler on 08/08/2021.
//
#include "OGLEApp.h"
#include <iostream>


class MyApp : public ogle::OgleApp
{
public:
    MyApp() : ogle::OgleApp(){};
    void onDraw() override{
        draw();
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

    void draw()
    {
        static float counter = 0;
        counter += .01f;

        //Transform The orthogonal Projection Matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-(float)1280/720,(float)1280/720, -0.5f, 0.5f, 0.5f, -0.5f);

        //Transform ModelView Matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        float t = (float)1/10;
        glPushMatrix();

        // scale, then rotate, then Translate
        glTranslatef(t * sin(counter),0,0);
        glRotatef(360*t * counter, 0,0,1);
        glScalef(0.5f,0.5f,0.5f);

        //Draw a Triangle!
        glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex3f(-0.5f,-0.5f,0);
        glColor3f(0,1,0);
        glVertex3f(0,0.5f,0);
        glColor3f(0,0,1);
        glVertex3f(0.5f,-0.5f,0);
        glEnd();

        glPopMatrix();


    }
};


int main()
{
    MyApp myApp;
    ogle::Interface::app = &myApp;
    myApp.initialize(1280,720);
    myApp.start();
    return 0;
}
