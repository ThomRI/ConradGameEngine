#include "AbstractLight.h"

using namespace glm;
using namespace std;

AbstractLight::AbstractLight(vec3 position, vec3 color, vec3 direction, float intensity, bool castShadow, float linearAttenuation, float quadraticAttenuation) :
    m_position(position), m_direction(direction), m_intensity(intensity), m_castShadow(castShadow), m_linearAttenuation(linearAttenuation), m_quadraticAttenuation(quadraticAttenuation)
{
    m_color.r = color[0];
    m_color.g = color[1];
    m_color.b = color[2];

    /* Generating view matrix */
    m_lookAt = lookAt(m_position, m_position + m_direction, vec3(UP_VECTOR));
}

void AbstractLight::sendShadowUniforms(const Shader &shader, size_t index)
{
    //TODO : Save the uniform locations once for shadows, don't retrieve it each frame...
    shader.sendMatrix(shader.getUniformLocation(uniform_str(index, "world")), m_world);

    /* Shadow map */
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "castShadow")), m_castShadow);
    if(m_castShadow) {
        shader.sendInt(shader.getUniformLocation(uniform_str(index, "shadowMapTex")), index + 10); // > 10 are for lights exclusively
        m_depthBuffer.bindTexture(index);
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

    // sprintf is slower.
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

vec3 AbstractLight::getDirection()
{
    return m_direction;
}

DepthBuffer &AbstractLight::getDepthBuffer()
{
    return m_depthBuffer;
}

mat4 AbstractLight::get_lookat()
{
    return m_lookAt;
}

void AbstractLight::setPosition(vec3 position)
{
    m_position = position;

    // Updating the light view matrix
    m_lookAt = m_lookAt = lookAt(m_position, m_position + m_direction, vec3(UP_VECTOR));
}

void AbstractLight::setDirection(vec3 direction)
{
    m_direction = direction;

    // Updating the light view matrix
    m_lookAt = m_lookAt = lookAt(m_position, m_position + m_direction, vec3(UP_VECTOR));
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
