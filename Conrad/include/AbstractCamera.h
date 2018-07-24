#ifndef ABSTRACTCAMERA_H
#define ABSTRACTCAMERA_H

/*!
 *  \file AbstractCamera.h
 */

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "scope.h"

#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define ONE_DEGREE_RAD M_PI/180 // One degree in radians

#define FORWARD     0
#define TRANSVERAL  1
#define UP          2

/*!
 *  \class AbstractCamera
 *  \brief Represents a generic camera. Provides virtual camera-related basic functions
 */
class AbstractCamera
{
    public:
        AbstractCamera();
        AbstractCamera(glm::vec3 initialPosition, glm::vec3 shiftSpeed);
        virtual ~AbstractCamera();

        /* Movements */
            virtual void forward();
            virtual void back();
            virtual void up();
            virtual void down();
            virtual void left();
            virtual void right();

            virtual void rotate(float dtheta, float dphi); // degrees

            virtual void move(); //Provides a function to call in order to update the positions/orientation from sub classes

        /* Setters */
        void setSpeed(glm::vec3 speed);
        void setSpeed(float forwardSpeed, float transversalSpeed, float upSpeed);

        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);

        /* Getters */
        glm::vec3 getUpVector();
        glm::mat4 &get_lookat();
        glm::vec3 getPos();

    protected:
        void update(); // updates the lookAt matrix

    private:
        glm::vec3 m_up = glm::vec3(UP_VECTOR);

        /* Orientation */
        float m_theta = M_PI / 2, m_phi = 0; // looking by the X-axis by default (radians)
        float m_x_sensitivity = 0.2, m_y_sensitivity = 0.2;
        glm::vec3 m_orientation, m_transversal; // transversal is always oriented to the left

        /* Position */
        glm::vec3 m_position = glm::vec3(0.0, 0.0, 0.0);

        /* Shifting */
        glm::vec3 m_shiftSpeed = glm::vec3(1.0, 1.0, 1.0); // Speed of translations (forward, transversal, up)

        /* OpenGL */
        glm::mat4 m_lookAt = glm::mat4(1.0); // identity by default

};

#endif // ABSTRACTCAMERA_H
