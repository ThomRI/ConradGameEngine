#include "FreeCamera.h"

FreeCamera::FreeCamera(InputManager *inputManager) :
    m_inputManager(inputManager)
{
    setSpeed(0.05, 0.05, 1.0);
}

void FreeCamera::move()
{
    if(m_inputManager->isKeyPressed(SDLK_z)) forward();
    if(m_inputManager->isKeyPressed(SDLK_s)) back();
    if(m_inputManager->isKeyPressed(SDLK_d)) right();
    if(m_inputManager->isKeyPressed(SDLK_q)) left();

    rotate(m_inputManager->getMouseYrel(), m_inputManager->getMouseXrel());
}

FreeCamera::~FreeCamera()
{
    //dtor
}
