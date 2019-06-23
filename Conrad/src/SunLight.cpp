#include "SunLight.h"

using namespace glm;

SunLight::SunLight(vec3 position, vec3 direction, vec3 color, float intensity, bool castShadow) :
    AbstractLight(position, color, direction, intensity, castShadow)
{

}

void SunLight::sendUniforms(const Shader &shader, size_t index)
{
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "type")), LIGHT_SUN);
    shader.sendRGB(shader.getUniformLocation(uniform_str(index, "color")), m_color);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "intensity")), m_intensity);
    shader.sendVector(shader.getUniformLocation(uniform_str(index, "direction")), m_direction);

    sendShadowUniforms(shader, index);
}

SunLight::~SunLight()
{
    //dtor
}
