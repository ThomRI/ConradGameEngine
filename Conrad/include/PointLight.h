#ifndef POINTLIGHT_H
#define POINTLIGHT_H

/*!
 *  \file PointLight.h
 */

#include "AbstractLight.h"

/* GLM */
#include <glm/glm.hpp>

/* Cross-plateform includes */
#ifdef WIN32
    #include <GL/glew.h>

#elif __APPLE__
    #define GL3_PROTOTYPES 1
    #include <OpenGL/gl3.h>

#else // UNIX / Linux
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>

#endif

/*!
 *  \class PointLight
 *  \brief Represents a point light (radial)
 */

class PointLight : public AbstractLight
{
    public:
        PointLight(glm::vec3 position, glm::vec3 color, float intensity = 1.0, float attenuation = 1.0);
        virtual ~PointLight();

        void sendUniforms(GLuint programID, size_t index);

    protected:

    private:
        /* World */
        float m_attenuation;

};

#endif // POINTLIGHT_H
