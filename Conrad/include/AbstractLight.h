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
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
#define LIGHT_SUN   2

/* Shadow mapping */
#define SHADOWMAP_SIZE 1024

/*!
 *  \class AbstractLight
 *  \brief Represents a generic source of light
 */
class AbstractLight
{
    public:
        AbstractLight(glm::vec3 position, glm::vec3 color, float intensity = 1.0, bool castShadow = false);
        virtual ~AbstractLight();

        virtual void sendUniforms(GLuint programID, size_t index) = 0; // Virtual pure
        virtual void sendShadowUniforms(GLuint programID, size_t index);

        /* Setters */
        void set_world(glm::mat4 world);

        /* Getters */
        glm::vec3 getPosition();
        GLuint getFrameBufferID();
        GLuint getDepthMapID();

        glm::mat4 get_lookat();
        glm::mat4 &get_world();

        bool castsShadow();

    protected:
        const char *uniform_str(size_t index, const char* property);

        /* World */
        float m_intensity;

        glm::vec3 m_position;
        glm::mat4 m_lookAt = glm::mat4(1.0);
        glm::mat4 m_world = glm::mat4(1.0);

        RGB       m_color;

        /* Shadow mapping */
        bool m_castShadow = false;
        GLuint  m_framebufferID,
                m_depthMapID;

    private:
};

#endif // ABSTRACTLIGHT_H
