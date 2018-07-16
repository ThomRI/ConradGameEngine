#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H


/*!
 * \file AbstractMesh.h
 * \author ThomRI
 * \version 0.1
 */

 #include "scope.h"
 #include <iostream>

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
        AbstractMesh(int verticesLength, int colorsLength, GLenum meshType);
        AbstractMesh(int verticesLength, int colorsLength, float *vertices, float *colors, GLenum meshType);
        virtual ~AbstractMesh();

        bool setVertices(float *vertices, int length);
        bool setColors(float *colors, int length);

        void load();
        void draw();

        glm::mat4 &get_modelview();

    protected:
        /* World */
        glm::mat4 m_modelview = glm::mat4(1.0);

    private:
        /* Mesh datas */
        float   *m_vertices,
                *m_colors,
                *m_texCoords;
        int m_verticesLength, // Number of vertices
            m_colorsLength;
        int m_verticesSize,
            m_colorsSize;

        /* OpenGL */
        GLuint  m_vboID,
                m_vaoID;
        GLenum m_meshType; // GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW

        bool m_loaded = false;

};

#endif // ABSTRACTMESH_H
