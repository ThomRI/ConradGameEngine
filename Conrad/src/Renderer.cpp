#include "Renderer.h"

using namespace std;
using namespace glm;

Renderer::Renderer()
{
    m_projection = perspective(70.0, 16.0/9, 1.0, 100.0);
    m_camera = new AbstractCamera;

    // Z UP X FORWARD
}

Renderer::Renderer(AbstractCamera *camera) :
    m_camera(camera)
{

}

void Renderer::setShader(Shader shader)
{
    m_shader = shader;
    if(!m_shader.load()) {
        cout << "Error loading the shader (app will most likely crash, please make sure your GLSL is valid)." << endl;
    }
}

void Renderer::render()
{
    glUseProgram(m_shader.getProgramID()); // Binding shader

    /* Camera */
    vec3 cameraPos = m_camera->getPos();
    glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "cameraPos"), cameraPos[0], cameraPos[1], cameraPos[2]);

        // VBOs and AttribPointers are token care of in AbstractMesh (by the VAO). Here we just send the matrices and call AbstractMesh::draw()

        for(vector<AbstractMesh*>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            // Sending matrices to the Shader
            (*mesh)->get_modelview() *= glm::rotate<float>(0.05, 0.0f, 0.0f, 1.0f);
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "camera"), 1, GL_FALSE, glm::value_ptr(m_camera->get_lookat()));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr((*mesh)->get_modelview()));

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "normalMatrix4"), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse((*mesh)->get_modelview()))));

            glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightPos"), 0.0, 0.0, 2.0);
            glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "lightColor"), 1.0, 1.0, 1.0);

            (*mesh)->draw();
        }


    glUseProgram(0);
}

void Renderer::toggleWireframe()
{
    if(m_wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    m_wireframe = !m_wireframe;
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

AbstractMesh *Renderer::getMesh(int meshID)
{
    if(meshID >= m_meshes.size() || meshID < 0) {
        return nullptr;
    }

    return m_meshes.at(meshID);
}

void Renderer::setCamera(AbstractCamera *camera)
{
    m_camera = camera;
}

AbstractCamera *Renderer::get_camera()
{
    return m_camera;
}

Renderer::~Renderer()
{
    //dtor
}
