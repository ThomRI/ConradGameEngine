#ifndef FREECAMERA_H
#define FREECAMERA_H

/*!
 *  \file FreeCamera.h
 */

#define KEY_MAP_AZERTY
#include "key_mapping.h"

#include "InputManager.h"
#include "AbstractCamera.h"

/*!
 *  \class FreeCamera
 *  \brief High-level class using the input system to provide a free-cam
 */

class FreeCamera : public AbstractCamera
{
    public:
        FreeCamera(InputManager *inputManager);
        virtual ~FreeCamera();

        void move();

    protected:

    private:
        InputManager *m_inputManager;
};

#endif // FREECAMERA_H
