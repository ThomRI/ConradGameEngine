#include "Application.h"

Application::Application(char *title, int width, int height) :
    m_width(width), m_height(height), m_title(title)
{
    m_renderer = new Renderer();
    m_inputManager = new InputManager();
}

/// \return The initialization status (false for failed, true for a success).
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

    // Version OpenGL 3.1
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

    /* OpenGL settings */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    /* Disabling vsync */
    SDL_GL_SetSwapInterval(0);

    std::cout << "Application initialized." << std::endl;

    return true;
}

/// \brief Main loop of an Application
void Application::loop(int const fps)
{
    ms delay(1000.0/fps);
    std::cout << "Starting app loop at " << fps << " fps" << std::endl;

    m_run = true;
    while(m_run && !m_inputManager->close()) {
        auto start = std::chrono::steady_clock::now();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_renderer->render();

        SDL_GL_SwapWindow(m_window);

        /* Inputs treatment here */
        m_inputManager->update();

        // consistent fps system
        auto delta = std::chrono::duration_cast<ms>(std::chrono::steady_clock::now() - start); // Time that remains to be waited before next frame
        if(delta < delay) {
            //std::cout << "FPS Fidelity : " << (delay - delta).count()*100 / delay.count() << "%" << std::endl; // For debug only : very slow !
            std::this_thread::sleep_for(delay - delta);
        }
    }
}

void Application::interrupt()
{
    m_run = false;
}

Renderer *Application::getRenderer()
{
    return m_renderer;
}

InputManager *Application::inputs()
{
    return m_inputManager;
}

Application::~Application()
{
    SDL_DestroyWindow(m_window);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}
