#ifndef ABSTRACTMESH_H
#define ABSTRACTMESH_H


/*!
 * \file AbstractMesh.h
 * \author ThomRI
 * \version 0.1
 */

 /* GLM */
 #include <glm.hpp>
 #include <gtx/transform.hpp>
 #include <gtc/type_ptr.hpp>

/*!
 * \class AbstractMesh AbstractMesh.h
 * \brief AbstractMesh represents an abstract mesh. This class provides a minimal support for meshes, and interfaces with the GPU for the loading process.
 */
class AbstractMesh
{
    public:
        AbstractMesh(int verticesLength, int colorsLength);
        AbstractMesh(int verticesLength, int colorsLength, float *vertices, float *colors, GLenum meshType);
        virtual ~AbstractMesh();

        bool setVertices(float *vertices, int length);
        bool setColors(float *colors, int length);

        void load();
        void draw();

        glm::mat4 &get_modelview();

    protected:
        /* World */
        glm::mat4 m_modelview = mat4(1.0);

    private:
        /* Mesh datas */
        float   *m_vertices,
                *m_colors,
                *m_texCoords;
        int m_verticesLength, // Number of vertices
            m_colorsLength;

        /* OpenGL */
        GLuint  m_vboID,
                m_vaoID;
        GLenum m_meshType; // GL_STATIC_DRAW / GL_DYNAMIC_DRAW / GL_STREAM_DRAW

        bool m_loaded = false;

};

#endif // ABSTRACTMESH_H
