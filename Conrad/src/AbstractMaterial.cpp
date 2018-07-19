#include "AbstractMaterial.h"

AbstractMaterial::AbstractMaterial()
{
    //ctor
}

AbstractMaterial::AbstractMaterial(RGB ambient, RGB diffuse, RGB specular, RGB emit, float specularExponent, float alpha) :
    m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_emit(emit), m_specularExponent(specularExponent), m_alpha(alpha)
{

}

/* #### GETTERS #### */

RGB AbstractMaterial::ambient()
{
    return m_ambient;
}

RGB AbstractMaterial::diffuse()
{
    return m_diffuse;
}

RGB AbstractMaterial::specular()
{
    return m_specular;
}

float AbstractMaterial::specularExponent()
{
    return m_specularExponent;
}

float AbstractMaterial::alpha()
{
    return m_alpha;
}

/* #### SETTERS #### */
void AbstractMaterial::setAmbient(RGB ambient)
{
    m_ambient = ambient;
}

void AbstractMaterial::setAmbient(float r, float g, float b)
{
    setAmbient({r, g, b});
}

void AbstractMaterial::setDiffuse(RGB diffuse)
{
    m_diffuse = diffuse;
}

void AbstractMaterial::setDiffuse(float r, float g, float b)
{
    setDiffuse({r, g, b});
}

void AbstractMaterial::setSpecular(RGB specular)
{
    m_specular = specular;
}

void AbstractMaterial::setSpecular(float r, float g, float b)
{
    setSpecular({r, g, b});
}

void AbstractMaterial::setEmit(RGB emit)
{
    m_emit = emit;
}

void AbstractMaterial::setEmit(float r, float g, float b)
{
    setEmit({r, g, b});
}

void AbstractMaterial::setSpecularExponent(float exponent)
{
    m_specularExponent = exponent;
}

void AbstractMaterial::setAlpha(float alpha)
{
    m_alpha = alpha;
}

AbstractMaterial::~AbstractMaterial()
{
    //dtor
}
