#include "AbstractMesh.h"

AbstractMesh::AbstractMesh(int verticesLength, int colorsLength, float *vertices, float *colors, GLenum meshType) :
    m_vertices(vertices), m_colors(colors), m_texCoords(texCoords), m_verticesLength(verticesLength), m_colorsLength(colorsLength), m_meshType(meshType)
{
    //ctor
}

/// \brief Uploads the mesh data to the GPU, getting the mesh ready to be drawn.
void AbstractMesh::load()
{
    /* ##### VBO ##### */

        /* Deleting a potential former VBO with same ID */
        if(glIsBuffer(m_vboID) == GL_TRUE) {
            glDeleteBuffers(1, &m_vboID);
        }

        /* Generating VBO */
        glGenBuffers(1, &m_vboID);

        /* Uploading datas */
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
            glBufferData(GL_ARRAY_BUFFER, 3 * (m_verticesLength + m_colorsLength) * sizeof(float), 0, m_meshType); // 3* for 3 coordinates each
            // TODO : Add Texture support in AbstractMesh

            glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesLength, m_vertices);
            glBufferSubData(GL_ARRAY_BUFFER, m_verticesLength, m_colorsLength, m_colors);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* ##### VAO ##### */

        /* Deleting a potential former VAO with same ID */
        if(glIsVertexArray(m_vaoID) == GL_TRUE) {
            glDeleteVertexArrays(1, &m_vaoID);
        }

        /* Generating VAO */
        glGenVertexArrays(1, &m_vaoID);

        /* Setting up VAO */
        glBindVertexArray(m_vaoID);

        /* GPU sided code from here */
            glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
                glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(VERTEX_BUFFER); // First enabled is VERTEX_BUFFER for the shader

                glVertexAttribPointer(COLOR_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesLength));
                glEnableVertexAttribArray(COLOR_BUFFER); // Second enabled is COLOR_BUFFER for the shader
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        /* End of GPU sided code */

        glBindVertexArray(0);
}

/// \return The modelview matrix of the mesh.
glm::mat4 &AbstractMesh::get_modelview()
{
    return m_modelview;
}

void AbstractMesh::draw()
{
    // /!\ Assumes the correct modelview matrix has already been sent

    glBindVertexArray(m_vaoID); // Using the VAO

        glDrawArrays(GL_TRIANGLES, 0, m_verticesLength);

    glBindVertexArray(0);
}

AbstractMesh::~AbstractMesh()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}
