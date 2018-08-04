#include "AbstractLight.h"

using namespace glm;
using namespace std;

AbstractLight::AbstractLight(vec3 position, vec3 color, float intensity, bool castShadow) :
    m_position(position), m_intensity(intensity), m_castShadow(castShadow)
{
    m_color.r = color[0];
    m_color.g = color[1];
    m_color.b = color[2];

    /* Generating view matrix */
    m_lookAt = lookAt(m_position, vec3(0.0), vec3(UP_VECTOR));
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

    /* WORKS BUT ACTUALLY SLOWER!
    if(index >= 100) return "error";

    size_t nbrDigits = 0;
    if(index < 10)  nbrDigits = 1;
    else            nbrDigits = 2;

    size_t size = (LIGHTS_ARRAY_STRLEN + nbrDigits + strlen(property) + 4) * sizeof(char); // lights[0].property, 4 is for [ ] . and \0

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

DepthBuffer &AbstractLight::getDepthBuffer()
{
    return m_depthBuffer;
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
