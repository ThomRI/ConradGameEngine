#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include "Renderer.h"

/* GLEW Initialization */
#ifdef WIN32
    #include <GL/glew.h>
#else
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>
#endif // WIN32

class Application
{
    public:
        Application(char *title, int width, int height);
        virtual ~Application();

        bool init(); // Initializes SDL window and OpenGL context
        void loop(int fps); // Main app loop

        Renderer *getRenderer();

    protected:

    private:
        /* Window */
        SDL_Window *m_window;
        int m_width, m_height;
        char *m_title;

        bool m_run = true;

        /* OpenGL */
        SDL_GLContext m_context;

        /* Rendering */
        Renderer *m_renderer;
};

#endif // APPLICATION_H
