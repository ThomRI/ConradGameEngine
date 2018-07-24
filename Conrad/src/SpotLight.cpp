#include "SpotLight.h"

using namespace glm;

SpotLight::SpotLight(vec3 position, vec3 color, vec3 direction, float coneAngle, float intensity, float attenuation) :
    AbstractLight(position, color, intensity), m_attenuation(attenuation), m_direction(direction), m_coneAngle(coneAngle)
{
    //ctor
}

void SpotLight::sendUniforms(GLuint programID, size_t index)
{
    glUniform1i(glGetUniformLocation(programID, uniform_str(index, "type")), LIGHT_SPOT);
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "position")), m_position[0], m_position[1], m_position[2]);
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "color")), m_color.r, m_color.g, m_color.b);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "intensity")), m_intensity);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "attenuation")), m_attenuation);

    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "direction")), m_direction[0], m_direction[1], m_direction[2]);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "coneAngle")), m_coneAngle);
}

SpotLight::~SpotLight()
{
    //dtor
}
