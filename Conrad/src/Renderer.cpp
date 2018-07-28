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
    m_uniformLocations.cameraPos = m_shader.getUniformLocation("cameraPos");
    m_uniformLocations.projection = m_shader.getUniformLocation("projection");
    m_uniformLocations.camera = m_shader.getUniformLocation("camera");
    m_uniformLocations.modelview = m_shader.getUniformLocation("modelview");
    m_uniformLocations.normalMatrix = m_shader.getUniformLocation("normalMatrix");
    m_uniformLocations.nbrLights = m_shader.getUniformLocation("nbrLights");

    m_uniformLocations.ambientColor = m_shader.getUniformLocation("ambientColor");
    m_uniformLocations.diffuseColor = m_shader.getUniformLocation("diffuseColor");
    m_uniformLocations.specularColor = m_shader.getUniformLocation("specularColor");

    m_uniformLocations.ambientStrength = m_shader.getUniformLocation("ambientStrength");
    m_uniformLocations.diffuseStrength = m_shader.getUniformLocation("diffuseStrength");
    m_uniformLocations.specularStrength = m_shader.getUniformLocation("specularStrength");
    m_uniformLocations.specularExponent = m_shader.getUniformLocation("specularExponent");

    // Diffuse texture
    m_shader.bind();
        m_shader.sendInt(m_shader.getUniformLocation("tex"), 0); // ID 0 for diffuse textures
    m_shader.unbind();
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
    m_shader.bind();

    /* Camera */
    vec3 cameraPos = m_camera->getPos();
    m_shader.sendVector(m_uniformLocations.cameraPos, cameraPos);

        // VBOs and AttribPointers are token care of in AbstractMesh (by the VAO). Here we just send the matrices and call AbstractMesh::draw()

        for(vector<AbstractMesh*>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            // Sending matrices to the Shader
            m_shader.sendMatrix(m_uniformLocations.projection, m_perspective);
            m_shader.sendMatrix(m_uniformLocations.camera, m_camera->get_lookat());
            m_shader.sendMatrix(m_uniformLocations.modelview, (*mesh)->get_modelview());

            m_shader.sendMatrix(m_uniformLocations.normalMatrix, glm::transpose(glm::inverse((*mesh)->get_modelview())));

            /* Lights */
            m_shader.sendInt(m_uniformLocations.nbrLights, m_lights.size());
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


            m_shader.sendRGB(m_uniformLocations.ambientColor, ambientColor);
            m_shader.sendRGB(m_uniformLocations.diffuseColor, diffuseColor);
            m_shader.sendRGB(m_uniformLocations.specularColor, specularColor);

            m_shader.sendFloat(m_uniformLocations.ambientStrength, ambientStrength);
            m_shader.sendFloat(m_uniformLocations.diffuseStrength, diffuseStrength);
            m_shader.sendFloat(m_uniformLocations.specularStrength, specularStrength);
            m_shader.sendFloat(m_uniformLocations.specularExponent, specularExponent);

            (*mesh)->draw();
        }


    m_shader.unbind();
}

void Renderer::generateShadowMap(AbstractLight *source)
{
    if(!source->castsShadow()) return; // No FBO, no depth texture...

    mat4 source_world = m_ortho * source->get_lookat();
    source->set_world(source_world);

    /* Rendering */
    glCullFace(GL_FRONT);
    m_depthShader.bind();
    glUniformMatrix4fv(glGetUniformLocation(m_depthShader.getProgramID(), "world"), 1, GL_FALSE, value_ptr(source_world));

    glViewport(0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE);
    glBindFramebuffer(GL_FRAMEBUFFER, source->getFrameBufferID());
    glClear(GL_DEPTH_BUFFER_BIT);

        for(vector<AbstractMesh*>::iterator mesh = m_meshes.begin();mesh != m_meshes.end();mesh++) { // Iterating over meshes
            glUniformMatrix4fv(glGetUniformLocation(m_depthShader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr((*mesh)->get_modelview())); // modelview of the mesh
            (*mesh)->draw();
        }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_depthShader.unbind();

    glCullFace(GL_BACK);
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
