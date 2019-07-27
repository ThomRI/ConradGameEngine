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

AbstractGUIObject::~AbstractGUIObject()
{
    //dtor
}
