#include "AbstractLight.h"

using namespace glm;
using namespace std;

AbstractLight::AbstractLight(vec3 position, vec3 color, float intensity, float attenuation) :
    m_position(position), m_intensity(intensity), m_attenuation(attenuation)
{
    m_color.r = color[0];
    m_color.g = color[1];
    m_color.b = color[2];
}

void AbstractLight::sendUniforms(GLuint programID, size_t index)
{
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "position")), m_position[0], m_position[1], m_position[2]);
    glUniform3f(glGetUniformLocation(programID, uniform_str(index, "color")), m_color.r, m_color.g, m_color.b);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "intensity")), m_intensity);
    glUniform1f(glGetUniformLocation(programID, uniform_str(index, "attenuation")), m_attenuation);
}

const char *AbstractLight::uniform_str(size_t index, const char* property)
{
    ostringstream ss;
    ss << LIGHTS_ARRAY_SHADER << "[" << index << "]." << property << '\0';

    return ss.str().c_str();
}

AbstractLight::~AbstractLight()
{
    //dtor
}
