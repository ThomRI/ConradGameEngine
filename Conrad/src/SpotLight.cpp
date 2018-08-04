#include "SpotLight.h"

using namespace glm;

SpotLight::SpotLight(vec3 position, vec3 color, vec3 direction, float coneAngle, float intensity, float attenuation, bool castShadow) :
    AbstractLight(position, color, intensity, castShadow), m_attenuation(attenuation), m_direction(direction), m_coneAngle(coneAngle)
{
    //ctor
}

void SpotLight::sendUniforms(const Shader &shader, size_t index)
{
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "type")), LIGHT_SPOT);

    shader.sendVector(shader.getUniformLocation(uniform_str(index, "position")), m_position);
    shader.sendRGB(shader.getUniformLocation(uniform_str(index, "color")), m_color);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "intensity")), m_intensity);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "attenuation")), m_attenuation);

    shader.sendVector(shader.getUniformLocation(uniform_str(index, "direction")), m_direction);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "coneAngle")), m_coneAngle);

    sendShadowUniforms(shader, index);
}

SpotLight::~SpotLight()
{
    //dtor
}
