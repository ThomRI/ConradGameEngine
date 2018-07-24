#include "AbstractLight.h"

using namespace glm;
using namespace std;

AbstractLight::AbstractLight(vec3 position, vec3 color, float intensity, bool castShadow) :
    m_position(position), m_intensity(intensity), m_castShadow(castShadow)
{
    m_color.r = color[0];
    m_color.g = color[1];
    m_color.b = color[2];

    if(m_castShadow) {
        /* Frame Buffer */
        glGenFramebuffers(1, &m_framebufferID);

        /* Depth map texture */
        glGenTextures(1, &m_depthMapID);
        glBindTexture(GL_TEXTURE_2D, m_depthMapID);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

        glBindTexture(GL_TEXTURE_2D, 0);

        /* Binding both */
        glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferID);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMapID, 0);
            glDrawBuffer(GL_NONE); // No color
            glReadBuffer(GL_NONE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        /* Generating view matrix */
        m_lookAt = lookAt(m_position, vec3(0.0), vec3(UP_VECTOR));
    }
}

const char *AbstractLight::uniform_str(size_t index, const char* property)
{
    ostringstream ss;
    ss << LIGHTS_ARRAY_SHADER << "[" << index << "]." << property << '\0';

    /* ss gets deleted after this function, and so does the ss.str().c_str() pointer */
    /* We thus need to copy the result in a memory bloc that won't get deleted by the function termination (using malloc) */
    char *out = (char*) malloc(ss.str().size());
    out = strncpy(out, ss.str().c_str(), ss.str().size());
    return out;

    /*
    if(index >= 100) return "error";

    size_t nbrDigits = 0;
    if(index < 10)  nbrDigits = 1;
    else            nbrDigits = 2;

    size_t size = (LIGHTS_ARRAY_STRLEN + nbrDigits + strlen(property) + 4) * sizeof(char); // lights[0].property, 3 is for [ ] . and \0

    char *out = (char*) malloc(size);
    sprintf(out, "%s[%s].%s", LIGHTS_ARRAY_SHADER, int100_to_str[index], property);

    return out;
    */
}

/* Setters */
void AbstractLight::set_world(mat4 world)
{
    m_world = world;
}

/* Getters */

vec3 AbstractLight::getPosition()
{
    return m_position;
}

GLuint AbstractLight::getFrameBufferID()
{
    return m_framebufferID;
}

GLuint AbstractLight::getDepthMapID()
{
    return m_depthMapID;
}

mat4 AbstractLight::get_lookat()
{
    return m_lookAt;
}

mat4 &AbstractLight::get_world()
{
    return m_world;
}

bool AbstractLight::castsShadow()
{
    return m_castShadow;
}

AbstractLight::~AbstractLight()
{
    //dtor
}
