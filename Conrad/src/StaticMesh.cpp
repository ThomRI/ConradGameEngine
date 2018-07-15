#include "StaticMesh.h"

StaticMesh::StaticMesh(int bufferLength, float *vertices, float *colors, float *texCoords = nullptr) :
    AbstractMesh(bufferLength, bufferLength, vertices, colors, GL_STATIC_DRAW)
{
    //ctor
}

StaticMesh::~StaticMesh()
{
    // dtor
}
