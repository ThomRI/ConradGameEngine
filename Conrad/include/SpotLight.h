#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "AbstractLight.h"
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

class SpotLight : public AbstractLight
{
    public:
        SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float coneAngle, float intensity = 1.0, float attenuation = 1.0);
        virtual ~SpotLight();

        void sendUniforms(GLuint programID, size_t index);

    protected:

    private:
        glm::vec3 m_direction;
        float m_coneAngle;
};

#endif // SPOTLIGHT_H
