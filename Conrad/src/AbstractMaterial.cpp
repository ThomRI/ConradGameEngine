#include "AbstractMaterial.h"

AbstractMaterial::AbstractMaterial()
{
    //ctor
}

AbstractMaterial::AbstractMaterial(RGB ambientColor, RGB diffuseColor, RGB specularColor, RGB emitColor, float specularExponent, float alpha, float ambientStrength, float diffuseStrength, float specularStrength, float emitStrength) :
    m_ambientColor(ambientColor), m_diffuseColor(diffuseColor), m_specularColor(specularColor), m_emitColor(emitColor), m_specularExponent(specularExponent), m_alpha(alpha), m_ambientStrength(ambientStrength), m_diffuseStrength(diffuseStrength), m_specularStrength(specularStrength), m_emitStrength(emitStrength)
{

}

/* #### GETTERS #### */

RGB AbstractMaterial::getAmbientColor()
{
    return m_ambientColor;
}

RGB AbstractMaterial::getDiffuseColor()
{
    return m_diffuseColor;
}

RGB AbstractMaterial::getSpecularColor()
{
    return m_specularColor;
}

RGB AbstractMaterial::getEmitColor()
{
    return m_emitColor;
}

float AbstractMaterial::getAmbientStrength()
{
    return m_ambientStrength;
}

float AbstractMaterial::getDiffuseStrength()
{
    return m_diffuseStrength;
}

float AbstractMaterial::getSpecularStrength()
{
    return m_specularStrength;
}

float AbstractMaterial::getEmitStrength()
{
    return m_emitStrength;
}

float AbstractMaterial::getSpecularExponent()
{
    return m_specularExponent;
}

float AbstractMaterial::getAlpha()
{
    return m_alpha;
}

AbstractTexture *AbstractMaterial::getDiffuseTexture()
{
    return m_diffuseTexture;
}

AbstractTexture *AbstractMaterial::getSpecularTexture()
{
    return m_specularTexture;
}

bool AbstractMaterial::isDiffuseTextured()
{
    return m_diffuseTextured;
}

bool AbstractMaterial::isSpecularTextured()
{
    return m_specularTextured;
}

/* #### SETTERS #### */
void AbstractMaterial::setAmbientColor(RGB color)
{
    m_ambientColor = color;
}

void AbstractMaterial::setAmbientColor(float r, float g, float b)
{
    setAmbientColor({r, g, b});
}

void AbstractMaterial::setDiffuseColor(RGB color)
{
    m_diffuseColor = color;
}

void AbstractMaterial::setDiffuseColor(float r, float g, float b)
{
    setDiffuseColor({r, g, b});
}

void AbstractMaterial::setSpecularColor(RGB color)
{
    m_specularColor = color;
}

void AbstractMaterial::setSpecularColor(float r, float g, float b)
{
    setSpecularColor({r, g, b});
}

void AbstractMaterial::setEmitColor(RGB color)
{
    m_emitColor = color;
}

void AbstractMaterial::setEmitColor(float r, float g, float b)
{
    setEmitColor({r, g, b});
}

void AbstractMaterial::setAmbientStrength(float strength)
{
    m_ambientStrength = strength;
}

void AbstractMaterial::setDiffuseStrength(float strength)
{
    m_diffuseStrength = strength;
}

void AbstractMaterial::setSpecularStrength(float strength)
{
    m_specularStrength = strength;
}

void AbstractMaterial::setEmitStrength(float strength)
{
    m_emitStrength = strength;
}

void AbstractMaterial::setSpecularExponent(float exponent)
{
    m_specularExponent = exponent;
}

void AbstractMaterial::setAlpha(float alpha)
{
    m_alpha = alpha;
}

void AbstractMaterial::setDiffuseTexture(AbstractTexture *texture)
{
    m_diffuseTexture = texture;
    m_diffuseTextured = true;
}

void AbstractMaterial::setSpecularTexture(AbstractTexture *texture)
{
    m_specularTexture = texture;
    m_specularTextured = true;
}

AbstractMaterial::~AbstractMaterial()
{
    //dtor
}
