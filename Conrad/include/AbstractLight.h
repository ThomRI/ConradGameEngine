#ifndef ABSTRACTLIGHT_H
#define ABSTRACTLIGHT_H

/*!
 *  \file AbstractLight.h
 */

#include <string>
#include <string.h>
#include <sstream>
#include "scope.h"


#include <iostream>

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

typedef unsigned int light_type;

/* Light types (must always be synchronized with the shader) */
#define LIGHT_POINT 0
#define LIGHT_SPOT  1

/*!
 *  \class AbstractLight
 *  \brief Represents a generic source of light
 */
class AbstractLight
{
    public:
        AbstractLight(glm::vec3 position, glm::vec3 color, float intensity = 1.0, float attenuation = 1.0);
        virtual ~AbstractLight();

        virtual void sendUniforms(GLuint programID, size_t index) = 0; // Virtual pure

    protected:
        const char *uniform_str(size_t index, const char* property);

        /* World */
        float m_intensity, m_attenuation;
        glm::vec3   m_position;
        RGB         m_color;
    private:
};

#endif // ABSTRACTLIGHT_H
