#include "DepthBuffer.h"

using namespace std;
using namespace glm;

DepthBuffer::DepthBuffer() :
    m_type(DEPTHBUFFER_SIMPLE)
{
    // Simple depth map by default
    load();
}

DepthBuffer::DepthBuffer(depthbuffer_type type) :
    m_type(type)
{
    load();
}

void DepthBuffer::load()
{
    /* The look at matrix determines what plane the orthogonal projection will be performed on */
    /* It can correspond to a light position and direction for example */

    /* Generating frame buffer */
    glGenFramebuffers(1, &m_frameBufferObjectID);

    /* Generating depth map texture */
    glGenTextures(1, &m_depthMapTextureID);
    glBindTexture(GL_TEXTURE_2D, m_depthMapTextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindTexture(GL_TEXTURE_2D, 0);

    /* Frame buffer texture attachment */
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObjectID);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapTextureID, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/// \brief Binds the attached texture
void DepthBuffer::bindTexture(size_t index)
{
    glActiveTexture(GL_TEXTURE0 + DEPTHBUFFER_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_depthMapTextureID);
}

/// \brief Binds the frame buffer
void DepthBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferObjectID);
}

DepthBuffer::~DepthBuffer()
{
    //dtor
}
