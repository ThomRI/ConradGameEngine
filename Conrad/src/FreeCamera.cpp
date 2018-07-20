#include "FreeCamera.h"

FreeCamera::FreeCamera(InputManager *inputManager) :
    m_inputManager(inputManager)
{
    setSpeed(0.05, 0.05, 1.0);
}

void FreeCamera::move()
{
    if(m_inputManager->isKeyPressed(KEY_Z)) forward();
    if(m_inputManager->isKeyPressed(KEY_S)) back();
    if(m_inputManager->isKeyPressed(KEY_D)) right();
    if(m_inputManager->isKeyPressed(KEY_Q)) left();

    rotate(m_inputManager->getMouseYrel(), m_inputManager->getMouseXrel());
}

FreeCamera::~FreeCamera()
{
    //dtor
}
