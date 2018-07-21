#include "AbstractMesh.h"

AbstractMesh::AbstractMesh(int verticesCount, int colorsCount, int texCount, GLenum meshType) :
    m_verticesCount(verticesCount), m_colorsCount(colorsCount), m_texCount(texCount), m_meshType(meshType)
{
    // This constructor is used to be able to use setVertices, setColors and setTexture (and ...) afterwards instead of pushing directly in the constructor. ALL OF THIS BEFORE LOADING THE MESH
}

AbstractMesh::AbstractMesh(int verticesCount, float *vertices, int colorsCount, float *colors, float *vertexNormals, GLenum meshType)
{
    AbstractMesh(verticesCount, vertices, colorsCount, colors, colorsCount, nullptr, vertexNormals, meshType); // Calling the texture-constructor with nullptr as texCoords.
}

// Texture constructor
AbstractMesh::AbstractMesh(int verticesCount, float *vertices, int colorsCount, float *colors, int texCount, float *texCoords, float *vertexNormals, GLenum meshType) :
    m_vertices(vertices), m_colors(colors), m_texCoords(texCoords), m_verticesCount(verticesCount), m_colorsCount(colorsCount), m_texCount(texCount), m_vertexNormals(vertexNormals), m_meshType(meshType)
{

}

/// \brief Sets up an blank texture. This is used to be compatible with the texturing system, without any effect on a pure-colors render.
void AbstractMesh::setBlankTex()
{
    /*m_texCoords = new float[m_texCount * 2];
    std::fill_n(m_texCoords, m_texCount * 2, 0.0); // Filling the texCoords with zeros (whatever if the texture is not used)*/

    AbstractTexture *tex_blank = new AbstractTexture(BLANKONE_PATH); // Using a one pixel 100% alpha texture (so that the texture can't be seen)
    m_material->setDiffuseTexture(tex_blank);
    if(!m_material->getDiffuseTexture()->load()) {
        std::cout << "Error while loading a non-textured mesh. App may crash." << std::endl;
    }
}

bool AbstractMesh::setVertices(float *vertices, int length)
{
    if(length != 3 * m_verticesCount || m_loaded) { // Already loaded means can't update vertices until I make the method to update VBO
        return false;
    }

    m_vertices = vertices;
    return true;

    //TODO : AbstractMesh::setVertices() : Update VBO
}

bool AbstractMesh::setColors(float *colors, int length)
{
    if(length != 3 * m_colorsCount || m_loaded) {
        return false;
    }

    m_colors = colors;
    return true;
}

bool AbstractMesh::setTexCoords(float *texCoords, int length)
{
    if(length != 2 * m_texCount || m_loaded) {
        return false;
    }

    m_texCoords = texCoords;
    return true;
}

bool AbstractMesh::setVertexNormals(float *vertexNormals, int length)
{
    if(length != 3 * m_verticesCount || m_loaded) {
        return false;
    }

    m_vertexNormals = vertexNormals;
    return true;
}

bool AbstractMesh::setMaterial(AbstractMaterial *material)
{
    m_material = material;
    return true; // Always succeeds
}

/// \brief Uploads the mesh data to the GPU, getting the mesh ready to be drawn (setting up VBO and VAO for the mesh).
void AbstractMesh::load()
{
    /* If no texture has been specified until here, we load a single pixel of alpha set to 1.0 with no color, in order to use the texture system but without any effect on the render */
    /* Note that the engine is created in order to always use a texture */
    if(!m_material->isDiffuseTextured()) {
        setBlankTex();
    }

    m_verticesSize = 3 * m_verticesCount * sizeof(float);
    m_colorsSize = 3 * m_colorsCount * sizeof(float);
    m_texSize = 2 * m_texCount * sizeof(float);
    m_vertexNormalsSize = m_verticesSize; // Easier for code maintenance

    /* ##### VBO ##### */

        /* Deleting a potential former VBO with same ID */
        if(glIsBuffer(m_vboID) == GL_TRUE) {
            glDeleteBuffers(1, &m_vboID);
        }

        /* Generating VBO */
        glGenBuffers(1, &m_vboID);

        /* Uploading datas */
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
            glBufferData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize + m_texSize + m_vertexNormalsSize, 0, m_meshType);

            glBufferSubData(GL_ARRAY_BUFFER, 0, m_verticesSize, m_vertices);                                                    // VERTICES
            glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize, m_colorsSize, m_colors);                                           // COLORS
            glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize, m_texSize, m_texCoords);                            // TEXTURE COORDS
            glBufferSubData(GL_ARRAY_BUFFER, m_verticesSize + m_colorsSize + m_texSize, m_vertexNormalsSize, m_vertexNormals);  // NORMAL OF EACH VERTEX (for light calculations)

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
                glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));                                                   // VERTICES
                glEnableVertexAttribArray(VERTEX_BUFFER); // First enabled is VERTEX_BUFFER for the shader

                glVertexAttribPointer(COLOR_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize));                                       // COLORS
                glEnableVertexAttribArray(COLOR_BUFFER); // Second enabled is COLOR_BUFFER for the shader

                glVertexAttribPointer(TEX_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize + m_colorsSize));                          // TEXTURE COORDS
                glEnableVertexAttribArray(TEX_BUFFER);

                glVertexAttribPointer(VERTEX_NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_verticesSize + m_colorsSize + m_texSize));    // NORMAL OF EACH VERTEX
                glEnableVertexAttribArray(VERTEX_NORMAL_BUFFER);
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

AbstractMaterial *AbstractMesh::getMaterial()
{
    return m_material;
}

void AbstractMesh::draw()
{
    // /!\ Assumes the correct modelview matrix has already been sent

    glBindVertexArray(m_vaoID); // Using the VAO

        m_material->getDiffuseTexture()->bind();
            glDrawArrays(GL_TRIANGLES, 0, m_verticesCount);
        m_material->getDiffuseTexture()->unbind();

    glBindVertexArray(0);
}

AbstractMesh::~AbstractMesh()
{
    glDeleteBuffers(1, &m_vboID);
    glDeleteVertexArrays(1, &m_vaoID);
}
