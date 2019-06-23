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
        SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float coneAngle, float spotExponent, float intensity = 1.0, bool castShadow = false, float linearAttenuation = 1.0, float minIntensity = 0.001, float maxDistance = 10.0);
        virtual ~SpotLight();

        void sendUniforms(const Shader &Shader, size_t index);

    protected:

    private:
        /* Cone */
        float m_coneAngle, m_spotExponent;
};

#endif // SPOTLIGHT_H
