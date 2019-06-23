#include "PointLight.h"

using namespace glm;

PointLight::PointLight(vec3 position, vec3 color, float intensity, bool castShadow, float linearAttenuation, float minIntensity, float maxDistance) :
    AbstractLight(position, color, vec3(0.0), intensity, castShadow, linearAttenuation, (intensity / (minIntensity * maxDistance * maxDistance)))
{
    //ctor
}

void PointLight::sendUniforms(const Shader &shader, size_t index)
{
    shader.sendInt(shader.getUniformLocation(uniform_str(index, "type")), LIGHT_POINT);
    shader.sendVector(shader.getUniformLocation(uniform_str(index, "position")), m_position);
    shader.sendRGB(shader.getUniformLocation(uniform_str(index, "color")), m_color);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "intensity")), m_intensity);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "linearAttenuation")), m_linearAttenuation);
    shader.sendFloat(shader.getUniformLocation(uniform_str(index, "quadAttenuation")), m_quadraticAttenuation);

    sendShadowUniforms(shader, index);
}

PointLight::~PointLight()
{
    //dtor
}
