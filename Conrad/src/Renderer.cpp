#include "Renderer.h"

using namespace std;
using namespace glm;

Renderer::Renderer()
{
    m_projection = perspective(70.0, 16.0/9, 0.001, 100.0);
    m_camera = new AbstractCamera;

    // Z UP Y FORWARD
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
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "camera"), 1, GL_FALSE, glm::value_ptr(m_camera->get_lookat()));
            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr((*mesh)->get_modelview()));

            glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "normalMatrix"), 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse((*mesh)->get_modelview()))));

            /* Lights */
            glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "nbrLights"), m_lights.size());
            for(int i = 0;i < m_lights.size();i++) {
                m_lights[i]->sendUniforms(m_shader.getProgramID(), i);
            }


            /* Material */

            RGB ambientColor = (*mesh)->getMaterial()->getAmbientColor(),
                diffuseColor = (*mesh)->getMaterial()->getDiffuseColor(),
                specularColor = (*mesh)->getMaterial()->getSpecularColor();

            float   ambientStrength = (*mesh)->getMaterial()->getAmbientStrength(),
                    diffuseStrength = (*mesh)->getMaterial()->getDiffuseStrength(),
                    specularStrength = (*mesh)->getMaterial()->getSpecularStrength(),
                    specularExponent = (*mesh)->getMaterial()->getSpecularExponent();

            glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "ambientColor"), ambientColor.r, ambientColor.g, ambientColor.b);
            glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "diffuseColor"), diffuseColor.r, diffuseColor.g, diffuseColor.b);
            glUniform3f(glGetUniformLocation(m_shader.getProgramID(), "specularColor"), specularColor.r, specularColor.g, specularColor.b);

            glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "ambientStrength"), ambientStrength);
            glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "diffuseStrength"), diffuseStrength);
            glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "specularStrength"), specularStrength);
            glUniform1f(glGetUniformLocation(m_shader.getProgramID(), "specularExponent"), specularExponent);

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

    return m_meshes[meshID];
}

int Renderer::addLight(AbstractLight *light)
{
    m_lights.push_back(light);
    return m_lights.size() - 1;
}

AbstractLight *Renderer::getLight(int lightID)
{
    if(lightID >= m_lights.size() || lightID < 0) {
        return nullptr;
    }

    return m_lights[lightID];
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
