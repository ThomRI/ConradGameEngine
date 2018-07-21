#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H


/*!
 * \file AbstractMesh.h
 * \author ThomRI
 * \version 0.1
 */

 #include "scope.h"
 #include <iostream>
 #include <algorithm>

 #include "AbstractTexture.h"
 #include "AbstractMaterial.h"

 /* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Cross-plateform includes */

#ifdef WIN32
    #include <GL/glew.h>

#elif __APPLE__
    #define GL3_PROTOTYPES 1
    #include <OpenGL/gl3.h>

#else // UNIX / Linux
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>

#endif

/*!
 * \class AbstractMesh AbstractMesh.h
 * \brief AbstractMesh represents an abstract mesh. This class provides a minimal support for meshes, and interfaces with the GPU for the loading process.
 */
class AbstractMesh
{
    public:
        AbstractMesh(int verticesCount, int colorsCount, int texCount, GLenum meshType);
        AbstractMesh(int verticesCount, float *vertices, int colorsCount, float *colors, float *vertexNormals, GLenum meshType);
        AbstractMesh(int verticesCount, float *vertices, int colorsCount, float *colors, int texCount, float *texCoords, float *vertexNormals, GLenum meshType);
        virtual ~AbstractMesh();

        bool setVertices(float *vertices, int length);
        bool setColors(float *colors, int length);
        bool setTexCoords(float *texCoords, int length);
        bool setVertexNormals(float *vertexNormals, int length);
        bool setMaterial(AbstractMaterial *material);

        void load();
        void draw();

        /* Getters */
        glm::mat4 &get_modelview();
        AbstractMaterial *getMaterial();

    protected:
        /* World */
        glm::mat4 m_modelview = glm::mat4(1.0);

        void setBlankTex();

    private:
        /* Mesh datas */
        float   *m_vertices,
                *m_colors,
                *m_texCoords,
                *m_vertexNormals; // Not faces normals ! There is one normal per vertex that has been averaged from the normals of the faces the vertex is involved in.

        AbstractMaterial *m_material = new AbstractMaterial;

        int m_verticesCount, // Number of vertices
            m_colorsCount,
            m_texCount; // No vertex normal count : it's the same as m_verticesCount as there will always be one normal per vertex.
        int m_verticesSize,
            m_colorsSize,
            m_texSize,
            m_vertexNormalsSize;

        /* OpenGL */
        GLuint  m_vboID = 0, // 0 is always unused
                m_vaoID = 0;
        GLenum m_meshType; // GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW

        bool m_loaded = false;
        bool m_tex_loaded = false;

};

#endif // ABSTRACTMESH_H
