#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

/*!
 *  \file DepthBuffer.h
 */

#include <iostream>
#include "scope.h"

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

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

typedef unsigned int depthbuffer_type;

// Types of depth buffer
#define DEPTHBUFFER_SIMPLE  0 // Simple texture is used
#define DEPTHBUFFER_CUBE    1 // Cube texture is used (useful for point lights)

/*!
 *  \class DepthBuffer
 *  \brief Contains depth informations from a given source point of view. This class is basically a depth texture handler.
 */
class DepthBuffer
{
    public:
        DepthBuffer(); // Uses simple depth map by default
        DepthBuffer(depthbuffer_type type);
        virtual ~DepthBuffer();

        void load();

        void bindTexture(size_t index);
        static inline void unbindTexture() { glBindTexture(GL_TEXTURE_2D, 0); };

        void bind();
        static inline void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); };

        /* Getters */
        GLsizei getShadowMapWidth();
        GLsizei getShadowMapHeight();
        GLuint getTextureID();

    protected:

    private:
        /* OpenGL */
        GLuint  m_frameBufferObjectID = 0,
                m_depthMapTextureID = 0; // The depth map is stored in a texture

        GLsizei m_shadowMapWidth = SHADOWMAP_SIZE, m_shadowMapHeight = SHADOWMAP_SIZE;
        depthbuffer_type m_type;
};

#endif // DEPTHBUFFER_H
