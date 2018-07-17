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
        AbstractMesh(int verticesLength, int colorsLength, int texLength, GLenum meshType);
        AbstractMesh(int verticesLength, float *vertices, int colorsLength, float *colors, int texLength, float *texCoords, GLenum meshType);
        AbstractMesh(int verticesLenght, float *vertices, int colorsLength, float *colors, GLenum meshType);
        virtual ~AbstractMesh();

        bool setVertices(float *vertices, int length);
        bool setColors(float *colors, int length);
        bool setTexCoords(float *texCoords, int length);
        bool setTexture(AbstractTexture *texture);

        void load();
        void draw();

        glm::mat4 &get_modelview();

    protected:
        /* World */
        glm::mat4 m_modelview = glm::mat4(1.0);

        void setupAlphaTex();

    private:
        /* Mesh datas */
        float   *m_vertices,
                *m_colors,
                *m_texCoords;

        AbstractTexture *m_texture;

        int m_verticesLength, // Number of vertices
            m_colorsLength,
            m_texLength;
        int m_verticesSize,
            m_colorsSize,
            m_texSize;

        /* OpenGL */
        GLuint  m_vboID,
                m_vaoID;
        GLenum m_meshType; // GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW

        bool m_loaded = false;
        bool m_tex_loaded = false;

};

#endif // ABSTRACTMESH_H
