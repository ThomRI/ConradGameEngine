#ifndef SUNLIGHT_H
#define SUNLIGHT_H

/*!
 *  \file SunLight.h
 */

#include "AbstractLight.h"

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // value_ptr

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
 *  \class SunLight
 *  \brief Represents a sun. The light behaves as directional only.
 */
class SunLight : public AbstractLight
{
    public:
        SunLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity = 1.0, bool castShadow = true);
        virtual ~SunLight();

        void sendUniforms(const Shader &shader, size_t index);

    protected:

    private:
        glm::vec3 m_direction;
};

#endif // SUNLIGHT_H
