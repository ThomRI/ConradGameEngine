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

const char *AbstractLight::uniform_str(size_t index, const char* property)
{
    ostringstream ss;
    ss << LIGHTS_ARRAY_SHADER << "[" << index << "]." << property << '\0';

    /* ss gets deleted after this function, and so does the ss.str().c_str() pointer */
    /* We thus need to copy the result in a memory bloc that won't get deleted by the function termination (using malloc) */
    char *out = (char*) malloc(ss.str().size());
    out = strncpy(out, ss.str().c_str(), ss.str().size());
    return out;
}

AbstractLight::~AbstractLight()
{
    //dtor
}
