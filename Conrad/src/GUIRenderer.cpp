#include "GUIRenderer.h"

GUIRenderer::GUIRenderer()
{
    //ctor
}

void GUIRenderer::load()
{
    /* Setting up VBO */
    if(glIsBuffer(m_vboID) == GL_TRUE) {
        glDeleteBuffers(1, &m_vboID);
    }

    glGenBuffers(1, &m_vboID);

    /* Setting up VAO */
    if(glIsVertexArray(m_vaoID) == GL_TRUE) {
        glDeleteVertexArrays(1, &m_vaoID);
    }

    glGenVertexArrays(1, &m_vaoID);

    glBindVertexArray(m_vaoID);

    /* Linking VAO and VBO */
        glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        // VERTEX1_X VERTEX1_Y TEX1_X TEX1_Y VERTEX2_X VERTEX2_Y TEX2_X TEX2_Y....

            glVertexAttribPointer(VERTEX_BUFFER, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(VERTEX_BUFFER);

            glVertexAttribPointer(TEX_BUFFER, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(sizeof(float) * 2)); // Begins after the two first vertices
            glEnableVertexAttribArray(TEX_BUFFER);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void GUIRenderer::addGUIObject(AbstractGUIObject *object)
{
    size_t size = object->getCoordsCount() * 2 * sizeof(float); // size of one array (only vertices for example, total size is 2*size to take into account texture coords)

    float *datas;
    datas = (float *) malloc(2 * size);

    float *vertices = object->getVertices();
    float *tex      = object->getTexCoords();

    // VERTEX1_X VERTEX1_Y TEX1_X TEX1_Y VERTEX2_X VERTEX2_Y TEX2_X TEX2_Y....
    for(int i = 0;i < object->getCoordsCount();i++) {
        datas[4*i]      = vertices[i];
        datas[4*i + 1]  = vertices[i+1];
        datas[4*i + 2]  = tex[i];
        datas[4*i + 3]  = tex[i+1];
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        glBufferData(GL_ARRAY_BUFFER, 2*size);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 2*size, datas);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_guiObjects.push_back(object);
}

void GUIRenderer::render()
{
    glBindVertexArray(m_vaoID); // Using the VAO
    // Each draw call will bind the associated texture if necessary.

        for(auto it = m_guiObjects.begin();it != m_guiObjects.end();it++) {
            it->draw();
        }

    glBindVertexArray(0);
}

GUIRenderer::~GUIRenderer()
{
    //dtor
}
