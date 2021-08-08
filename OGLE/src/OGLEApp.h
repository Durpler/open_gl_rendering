//
// Created by Durpler on 08/08/2021.
//

#ifndef OGLE_OGLEAPP_H
#define OGLE_OGLEAPP_H

#include "OGLEWindow.h"

namespace ogle
{
    /*
     * This is our base application class which can be inherited and altered in the actual application
     */
    class OgleApp
    {
    public:
        OgleApp();
        ~OgleApp();

        // delete copy constructors... This is an app!
        OgleApp(const OgleApp& other) = delete;
        OgleApp& operator=(const OgleApp& other) = delete;


        bool initialize(int width = 800, int height = 600);
        void start();

        // callbacks
        virtual void onDraw() {}

        virtual void onMouseMove(int x, int y){}

        virtual void onMouseDown(int button, int action){}

        virtual void onKeyDown(int key, int action){}

    private:
        int m_Width;
        int m_Height;

        OgleWindow m_AppWindow;


    };
}

#endif //OGLE_OGLEAPP_H
