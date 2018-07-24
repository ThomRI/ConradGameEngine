#include "PointLight.h"

using namespace glm;

PointLight::PointLight(vec3 position, vec3 color, float intensity, float attenuation) :
    AbstractLight(position, color, intensity, attenuation)
{
    //ctor
}

void PointLight::sendUniforms(GLuint programID, size_t index)
{
    glUniform1i(glGetUniformLocation(programID, uniform_str(index, "type")), LIGHT_POINT);
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "position")), m_position[0], m_position[1], m_position[2]);
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "color")), m_color.r, m_color.g, m_color.b);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "intensity")), m_intensity);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "attenuation")), m_attenuation);
}

PointLight::~PointLight()
{
    //dtor
}
