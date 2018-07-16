#include "StaticMesh.h"

StaticMesh::StaticMesh(int bufferLength) :
    AbstractMesh(bufferLength, bufferLength, GL_STATIC_DRAW)
{

}

StaticMesh::StaticMesh(int bufferLength, float *vertices, float *colors) :
    AbstractMesh(bufferLength, bufferLength, vertices, colors, GL_STATIC_DRAW)
{
    //ctor
}

StaticMesh::~StaticMesh()
{
    // dtor
}
