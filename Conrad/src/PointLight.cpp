#include "PointLight.h"

using namespace glm;

PointLight::PointLight(vec3 position, vec3 color, float intensity, float attenuation, bool castShadow) :
    AbstractLight(position, color, intensity, castShadow), m_attenuation(attenuation)
{
    //ctor
}

void PointLight::sendUniforms(const Shader &shader, size_t index)
{
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "type")), LIGHT_POINT);
    shader.sendVector(shader.getUniformLocation(uniform_str(index, "position")), m_position);
    shader.sendRGB(shader.getUniformLocation(uniform_str(index, "color")), m_color);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "intensity")), m_intensity);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "attenuation")), m_attenuation);

    sendShadowUniforms(shader, index);
}

PointLight::~PointLight()
{
    //dtor
}
