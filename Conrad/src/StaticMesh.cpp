#include "StaticMesh.h"

StaticMesh::StaticMesh(int bufferLength) :
    AbstractMesh(bufferLength, bufferLength, bufferLength, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferLength, float *vertices, float *colors) :
    AbstractMesh(bufferLength, vertices, bufferLength, colors, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferLength, float *vertices, float *colors, float *texCoords) :
    AbstractMesh(bufferLength, vertices, bufferLength, colors, bufferLength, texCoords, GL_STATIC_DRAW)
{
    // ctor
}

StaticMesh::~StaticMesh()
{
    // dtor
}
