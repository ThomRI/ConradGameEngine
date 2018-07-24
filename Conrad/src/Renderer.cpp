#include "Renderer.h"

using namespace std;
using namespace glm;

Renderer::Renderer(float viewport_width, float viewport_height) :
    m_viewport_width(viewport_width), m_viewport_height(viewport_height)
{
    m_perspective   = perspective(70.0, 16.0/9, 0.001, 100.0);
    m_ortho         = ortho(-30.0, 30.0, -30.0, 30.0, 0.1, 100.0);

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

    /* Uniforms */
    m_uniformLocations.cameraPos = glGetUniformLocation(m_shader.getProgramID(), "cameraPos");
    m_uniformLocations.projection = glGetUniformLocation(m_shader.getProgramID(), "projection");
    m_uniformLocations.camera = glGetUniformLocation(m_shader.getProgramID(), "camera");
    m_uniformLocations.modelview = glGetUniformLocation(m_shader.getProgramID(), "modelview");
    m_uniformLocations.normalMatrix = glGetUniformLocation(m_shader.getProgramID(), "normalMatrix");
    m_uniformLocations.nbrLights = glGetUniformLocation(m_shader.getProgramID(), "nbrLights");

    m_uniformLocations.ambientColor = glGetUniformLocation(m_shader.getProgramID(), "ambientColor");
    m_uniformLocations.diffuseColor = glGetUniformLocation(m_shader.getProgramID(), "diffuseColor");
    m_uniformLocations.specularColor = glGetUniformLocation(m_shader.getProgramID(), "specularColor");

    m_uniformLocations.ambientStrength = glGetUniformLocation(m_shader.getProgramID(), "ambientStrength");
    m_uniformLocations.diffuseStrength = glGetUniformLocation(m_shader.getProgramID(), "diffuseStrength");
    m_uniformLocations.specularStrength = glGetUniformLocation(m_shader.getProgramID(), "specularStrength");
    m_uniformLocations.specularExponent = glGetUniformLocation(m_shader.getProgramID(), "specularExponent");

    // Diffuse texture
    glUseProgram(m_shader.getProgramID());
        glUniform1i(glGetUniformLocation(m_shader.getProgramID(), "tex"), 0); // ID 0 for diffuse textures
    glUseProgram(0);
}

void Renderer::setDepthShader(Shader shader)
{
    m_depthShader = shader;
    if(!m_depthShader.load()) {
        cout << "Error loading the depth shader." << endl;
    }
}

void Renderer::render()
{
    glUseProgram(m_shader.getProgramID()); // Binding shader

    /* Camera */
    vec3 cameraPos = m_camera->getPos();
    glUniform3f(m_uniformLocations.cameraPos, cameraPos[0], cameraPos[1], cameraPos[2]);

        // VBOs and AttribPointers are token care of in AbstractMesh (by the VAO). Here we just send the matrices and call AbstractMesh::draw()

        for(vector<AbstractMesh*>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            // Sending matrices to the Shader
            glUniformMatrix4fv(m_uniformLocations.projection, 1, GL_FALSE, glm::value_ptr(m_perspective));
            glUniformMatrix4fv(m_uniformLocations.camera, 1, GL_FALSE, glm::value_ptr(m_camera->get_lookat()));
            glUniformMatrix4fv(m_uniformLocations.modelview, 1, GL_FALSE, glm::value_ptr((*mesh)->get_modelview()));

            glUniformMatrix4fv(m_uniformLocations.normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse((*mesh)->get_modelview()))));

            /* Lights */
            glUniform1i(m_uniformLocations.nbrLights, m_lights.size());
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

            glUniform3f(m_uniformLocations.ambientColor, ambientColor.r, ambientColor.g, ambientColor.b);
            glUniform3f(m_uniformLocations.diffuseColor, diffuseColor.r, diffuseColor.g, diffuseColor.b);
            glUniform3f(m_uniformLocations.specularColor, specularColor.r, specularColor.g, specularColor.b);

            glUniform1f(m_uniformLocations.ambientStrength, ambientStrength);
            glUniform1f(m_uniformLocations.diffuseStrength, diffuseStrength);
            glUniform1f(m_uniformLocations.specularStrength, specularStrength);
            glUniform1f(m_uniformLocations.specularExponent, specularExponent);

            (*mesh)->draw();
        }


    glUseProgram(0);
}

void Renderer::generateShadowMap(AbstractLight *source)
{
    if(!source->castsShadow()) return; // No FBO, no depth texture...

    mat4 source_world = m_ortho * source->get_lookat();
    source->set_world(source_world);

    /* Rendering */
    glUseProgram(m_depthShader.getProgramID());
    glUniformMatrix4fv(glGetUniformLocation(m_depthShader.getProgramID(), "world"), 1, GL_FALSE, value_ptr(source_world));

    glViewport(0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE);
    glBindFramebuffer(GL_FRAMEBUFFER, source->getFrameBufferID());
    glClear(GL_DEPTH_BUFFER_BIT);

        for(vector<AbstractMesh*>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            glUniformMatrix4fv(glGetUniformLocation(m_depthShader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr((*mesh)->get_modelview())); // modelview of the mesh
            (*mesh)->draw();
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);

    glViewport(0, 0, m_viewport_width, m_viewport_height);
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
