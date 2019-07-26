#include "AbstractGUIObject.h"

AbstractGUIObject::AbstractGUIObject(float *vertices, float *texCoords, int coordsCount) :
    m_vertices(vertices), m_texCoords(texCoords), m_coordsCount(coordsCount)
{

}

void AbstractGUIObject::draw() // In case of default texture quad used
{

}

AbstractGUIObject::~AbstractGUIObject()
{
    //dtor
}
