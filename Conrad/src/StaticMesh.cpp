#include "StaticMesh.h"

StaticMesh::StaticMesh(int bufferCount) :
    AbstractMesh(bufferCount, bufferCount, bufferCount, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferCount, float *vertices, float *colors) :
    AbstractMesh(bufferCount, vertices, bufferCount, colors, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferCount, float *vertices, float *colors, float *texCoords) :
    AbstractMesh(bufferCount, vertices, bufferCount * 3, colors, bufferCount, texCoords, GL_STATIC_DRAW)
{
    // ctor
}

StaticMesh::~StaticMesh()
{
    // dtor
}
