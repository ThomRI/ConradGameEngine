#include "InputManager.h"

InputManager::InputManager()
{
    /* Initializing input arrays */
    std::fill_n(m_keys, SDL_NUM_SCANCODES, false);
    std::fill_n(m_mouse, 8, false);
}

void InputManager::update()
{
    /* Reseting relative events */
    m_xrel = 0;
    m_yrel = 0;

    while(SDL_PollEvent(&m_events)) { /* Iterating over buffered registered inputs */
        switch(m_events.type) {

            /* Keyboard events */
                case SDL_KEYDOWN:
                    m_keys[m_events.key.keysym.scancode] = true;
                break;

                case SDL_KEYUP:
                    m_keys[m_events.key.keysym.scancode] = false;
                break;

            /* Mouse events */
                case SDL_MOUSEBUTTONDOWN:
                    m_mouse[m_events.button.button] = true;
                break;

                case SDL_MOUSEBUTTONUP:
                    m_mouse[m_events.button.button] = false;
                break;

                case SDL_MOUSEMOTION:
                    m_x = m_events.motion.x;
                    m_y = m_events.motion.y;

                    m_xrel = m_events.motion.xrel;
                    m_yrel = m_events.motion.yrel;
                break;

            /* Window events */
                case SDL_WINDOWEVENT:
                    m_close = (m_events.window.event == SDL_WINDOWEVENT_CLOSE);
                break;

            default: break;
        }
    }
}

bool InputManager::isKeyPressed(int scancode)
{
    if(scancode >= SDL_NUM_SCANCODES || scancode < 0) return false; // Avoids segfault from reading an invalid key
    return m_keys[scancode];
}

bool InputManager::isMousePressed(int code)
{
    if(code >= 8 || code < 0) return false;
    return m_mouse[code];
}

int InputManager::getMouseX()
{
    return m_x;
}

int InputManager::getMouseY()
{
    return m_y;
}

int InputManager::getMouseXrel()
{
    return m_xrel;
}

int InputManager::getMouseYrel()
{
    return m_yrel;
}

bool InputManager::close()
{
    return m_close;
}

InputManager::~InputManager()
{
    //dtor
}
