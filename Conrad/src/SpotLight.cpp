#include "SpotLight.h"

using namespace glm;

SpotLight::SpotLight(vec3 position, vec3 color, vec3 direction, float coneAngle, float spotExponent, float intensity, bool castShadow, float linearAttenuation, float minIntensity, float maxDistance) :
    AbstractLight(position, color, direction, intensity, castShadow, linearAttenuation, (intensity / (minIntensity * maxDistance * maxDistance))), m_coneAngle(coneAngle), m_spotExponent(spotExponent)
{

}

void SpotLight::sendUniforms(const Shader &shader, size_t index)
{
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "type")), LIGHT_SPOT);

    shader.sendVector(shader.getUniformLocation(uniform_str(index, "position")), m_position);
    shader.sendRGB(shader.getUniformLocation(uniform_str(index, "color")), m_color);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "intensity")), m_intensity);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "linearAttenuation")), m_linearAttenuation);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "quadAttenuation")), m_quadraticAttenuation);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "spotExponent")), m_spotExponent);

    shader.sendVector(shader.getUniformLocation(uniform_str(index, "direction")), m_direction);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "coneAngle")), m_coneAngle);

    sendShadowUniforms(shader, index);
}

SpotLight::~SpotLight()
{
    //dtor
}
