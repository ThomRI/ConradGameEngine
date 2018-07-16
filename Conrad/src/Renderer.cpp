#include "Renderer.h"

using namespace std;

Renderer::Renderer(Shader shader) :
    m_shader(shader)
{
    m_shader.load(); // Compiling and uploading shader
}

void Renderer::render()
{
    glUseProgram(m_shader.getProgramID());
    /* Shader enabled */

        // VBOs and AttribPointers are token care of in AbstractMesh (by the VAO). Here we just send the matrices and call AbstractMesh::draw()

        for(vector<*AbstractMesh>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            // Sending matrices to the Shader
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection", 1, GL_FALSE, value_ptr(m_projection)));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview", 1, GL_FALSE, value_ptr(m_global_modelview * (*mesh)->get_modelview())));

            (*mesh)->draw();
        }


    glUseProgram(0);
}

/*!
 * \brief Adds a mesh to the mesh list.
 * \return (int) Mesh ID for this renderer.
 */
int Renderer::addMesh(AbstractMesh *mesh)
{
    m_meshes.push_back(mesh);
    return m_meshes.size() - 1; // location of the mesh in the vector
}

AbstractMesh *Renderer:getMesh(int meshID)
{
    if(meshID >= m_meshes.size() || meshID < 0) {
        return nullptr;
    }

    return m_meshes.at(meshID);
}

Renderer::~Renderer()
{
    //dtor
}
