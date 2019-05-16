#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL.h>
#include <algorithm>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();

        void update();
        bool close();

        bool isKeyPressed(int scancode);
        bool isMousePressed(int code);

        inline int getMouseX();
        inline int getMouseY();

        inline int getMouseXrel();
        inline int getMouseYrel();

    protected:

    private:
        SDL_Event m_events;
        bool    m_keys[SDL_NUM_SCANCODES],
                m_mouse[8];

        int m_x = 0,
            m_y = 0,
            m_xrel = 0,
            m_yrel = 0;

        bool m_close = false;
};

inline int InputManager::getMouseX()
{
    return m_x;
}

inline int InputManager::getMouseY()
{
    return m_y;
}

inline int InputManager::getMouseXrel()
{
    return m_xrel;
}

inline int InputManager::getMouseYrel()
{
    return m_yrel;
}

#endif // INPUTMANAGER_H
