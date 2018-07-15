#include "Application.h"

Application::Application(char *title, int width, int height) :
    m_width(width), m_height(height), m_title(title)
{
    //ctor
}

bool Application::init()
{
    // SDL init
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    // Window creation
    m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(m_window == 0) {
        return false;
    }


    /* OpenGL Context */

    // Version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_context = SDL_GL_CreateContext(m_window);
    if(m_context == 0) {
        return false;
    }

    #ifdef WIN32 /* GLEW initialization for Windows */
        GLenum glew = glewInit();
        if(glew != GLEW_OK) {
            return false;
        }
    #endif // WIN32


    return true;
}

void Application::loop()
{
    while(m_run) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            /* Render here */

        SDL_GL_SwapWindow(m_window);
    }
}

Application::~Application()
{
    SDL_DestroyWindow(m_window);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}
