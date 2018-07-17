#include "AbstractMesh.h"

AbstractMesh::AbstractMesh(int verticesLength, int colorsLength, int texLength, GLenum meshType) :
    m_verticesLength(verticesLength), m_colorsLength(colorsLength), m_texLength(texLength), m_meshType(meshType)
{

}

AbstractMesh::AbstractMesh(int verticesLength, float *vertices, int colorsLength, float *colors, int texLength, float *texCoords, GLenum meshType) :
    m_vertices(vertices), m_colors(colors), m_texCoords(texCoords), m_verticesLength(verticesLength), m_colorsLength(colorsLength), m_texLength(texLength), m_meshType(meshType)
{
    if(m_texCoords == nullptr) {
        m_texCoords = new float[texLength * 3];
        std::fill_n(m_texCoords, texLength * 3, 0.0); // Filling the texCoords with zeros (whatever if the texture is not used)


    }
}

AbstractMesh::AbstractMesh(int verticesLength, float *vertices, int colorsLength, float *colors, GLenum meshType)
{
    AbstractMesh(verticesLenght, vertices, colorsLength, colors, colorsLength, nullptr, meshType); // Calling the texture-constructor with nullptr as texCoords.
}

bool AbstractMesh::setVertices(float *vertices, int length)
{
    if(length != 3 * m_verticesLength || m_loaded) { // Already loaded means can't update vertices until I make the method to update VBO
        return false;
    }

    m_vertices = vertices;
    return true;

    //TODO : AbstractMesh::setVertices() : Update VBO
}

bool AbstractMesh::setColors(float *colors, int length)
{
    if(length != 3 * m_colorsLength || m_loaded) {
        return false;
    }

    m_colors = colors;
    return true;
}

bool AbstractMesh::setTexCoords(float *texCoords, int length)
{
    if(length != 3 * m_colorsLength || m_loaded) {
        return false;
    }

    m_texCoords = texCoords;
    return true;
}

bool AbstractMesh::setTexture(AbstractTexture *texture)
{
    if(m_loaded) return false; // A loaded mesh can't be updated (for now)
    // TODO : Allow an abstract mesh to be update after loading

    m_texture = texture;
    return m_texture->load();
}

/// \brief Uploads the mesh data to the GPU, getting the mesh ready to be drawn (setting up VBO and VAO for the mesh).
void AbstractMesh::load()
{
    m_verticesSize = 3 * m_verticesLength * sizeof(float);
    m_colorsSize = 3 * m_colorsLength * sizeof(float);
    m_texSize = 3 * m_texLength * sizeof(float);

    /* ##### VBO ##### */

        /* Deleting a potential former VBO with same ID */
        if(glIsBuffer(m_vboID) == GL_TRUE) {
            glDeleteBuffers(1, &m_vboID);
        }

        /* Generating VBO */
        glGenBuffers(1, &m_vboID);

        /* Uploading datas */
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
            glBufferData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize + m_texSize, 0, m_meshType);

            glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesSize, m_vertices);
            glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize, m_colorsSize, m_colors);
            if(m_usesTex) glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize, m_texSize, m_texCoords);

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

        /* GPU sided code from here (stored in the VAO) */
            glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
                glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                glEnableVertexAttribArray(VERTEX_BUFFER); // First enabled is VERTEX_BUFFER for the shader

                glVertexAttribPointer(COLOR_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize));
                glEnableVertexAttribArray(COLOR_BUFFER); // Second enabled is COLOR_BUFFER for the shader

                glVertexAttribPointer(TEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize + m_colorsSize));
                glEnableVertexAttribArray(TEX_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        /* End of GPU sided code */

        glBindVertexArray(0);

        m_loaded = true;
}

/// \return The modelview matrix of the mesh (reference)
glm::mat4 &AbstractMesh::get_modelview()
{
    return m_modelview;
}

void AbstractMesh::draw()
{
    // /!\ Assumes the correct modelview matrix has already been sent

    glBindVertexArray(m_vaoID); // Using the VAO

        m_texture->bind();
        glDrawArrays(GL_TRIANGLES, 0, m_verticesLength);
        m_texture->unbind();

    glBindVertexArray(0);
}

AbstractMesh::~AbstractMesh()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}
