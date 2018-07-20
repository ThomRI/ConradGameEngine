#ifndef APPLICATION_H
#define APPLICATION_H

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <chrono>
#include <thread>

#include "Renderer.h"
#include "InputManager.h"

#define KEY_MAP_AZERTY
#include "key_mapping.h"

/* GLEW Initialization */
#ifdef WIN32
    #include <GL/glew.h>
#else
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>
#endif // WIN32

/* Timing */
using ms = std::chrono::duration<float, std::milli>;

class Application
{
    public:
        Application(char *title, int width, int height);
        virtual ~Application();

        bool init(); // Initializes SDL window and OpenGL context
        void loop(int const fps); // Main app loop
        void interrupt();

        Renderer *getRenderer();
        InputManager *getInputManager(); // Used by other classes to retrieve active inputs.

    protected:
        void toggleWireframe();

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

        /* Input management */
        InputManager *m_inputManager;
};

#endif // APPLICATION_H
