#include "AbstractGUIObject.h"

using namespace glm;

AbstractGUIObject::AbstractGUIObject()
{
    // Default ctor
}

AbstractGUIObject::AbstractGUIObject(float *vertices, float *texCoords, int coordsCount) :
    m_vertices(vertices), m_texCoords(texCoords), m_coordsCount(coordsCount)
{

}

void AbstractGUIObject::setData(float *vertices, float *texCoords, int coordsCount)
{
    // Assumes previous data have been deleted, so does a copy

    size_t size = sizeof(float) * 2 * coordsCount;

    m_vertices = (float *) malloc(size);
    m_texCoords = (float *) malloc(size);

    memcpy(m_vertices, vertices, size);
    memcpy(m_texCoords, texCoords, size);

    m_coordsCount = coordsCount;
}

void AbstractGUIObject::setPosition(float x, float y)
{
    m_modelview = mat4();
    m_modelview *= glm::translate(x, y, 0.0f);
}

void AbstractGUIObject::setPosition(vec2 position)
{
    setPosition(position.x, position.y);
}

void AbstractGUIObject::translate(float x, float y)
{
    m_modelview *= glm::translate(x, y, 0.0f);
}

void AbstractGUIObject::translate(vec2 vector)
{
    this->translate(vector.x, vector.y);
}

void AbstractGUIObject::rotate(float angle)
{
    m_modelview *= glm::rotate(angle, 0.0f, 0.0f, 1.0f);
}

void AbstractGUIObject::scale(float x, float y)
{
    m_modelview *= glm::scale(x, y, 0.0f);
}

void AbstractGUIObject::scale(float scale)
{
    m_modelview *= glm::scale(scale, scale, 0.0f);
}

float *AbstractGUIObject::getVertices()
{
    return m_vertices;
}

float *AbstractGUIObject::getTexCoords()
{
    return m_texCoords;
}

int AbstractGUIObject::getCoordsCount()
{
    return m_coordsCount;
}

mat4 &AbstractGUIObject::getModelview()
{
    return m_modelview;
}

AbstractGUIObject::~AbstractGUIObject()
{
    //dtor
}
