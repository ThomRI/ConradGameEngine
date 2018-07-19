#ifndef STATICMESH_H
#define STATICMESH_H

/*!
 * \file StaticMesh.h
 * \author ThomRI
 * \version 0.1
 */

#include "AbstractMesh.h"

/*!
 * \class StaticMesh StaticMesh.h
 * \brief StaticMesh represents a drawable mesh with fixed vertices. No vertex coordinate can be updated.
 */
class StaticMesh : public AbstractMesh
{
    public:
        StaticMesh(int bufferCount);
        StaticMesh(int bufferCount, float *vertices, float *colors, float *vertexNormals); // bufferLength is a NUMBER OF VERTICES (not a byte size)
        StaticMesh(int bufferCount, float *vertices, float *colors, float *texCoords, float *vertexNormals);
        virtual ~StaticMesh();

    protected:

    private:

};

#endif // STATICMESH_H
