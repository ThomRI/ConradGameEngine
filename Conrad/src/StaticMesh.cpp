#include "StaticMesh.h"

StaticMesh::StaticMesh(int bufferCount) :
    AbstractMesh(bufferCount, bufferCount, bufferCount, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferCount, float *vertices, float *colors, float *vertexNormals) :
    AbstractMesh(bufferCount, vertices, bufferCount, colors, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferCount, float *vertices, float *colors, float *texCoords, float *vertexNormals) :
    AbstractMesh(bufferCount, vertices, bufferCount, colors, bufferCount, texCoords, vertexNormals, GL_STATIC_DRAW)
{
    // ctor
}

StaticMesh::~StaticMesh()
{
    // dtor
}
