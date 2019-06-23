#ifndef RENDERER_H
#define RENDERER_H

/*!
 * \file Renderer.h
 * \author ThomRI
 * \version 0.1
 */

#include <vector>

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utilities.hpp"

#include "Shader.h"
#include "AbstractMesh.h"
#include "AbstractCamera.h"
#include "AbstractLight.h"

/*!
 * \class Renderer
 * \brief This class takes care of the rendering process for a given list of meshes.
 */
class Renderer
{
    public:
        Renderer(float viewport_width, float viewport_height);
        Renderer(AbstractCamera *camera);
        virtual ~Renderer();

        void setShader(Shader shader);
        void setDepthShader(Shader shader);

        void render(); // Pushes next frame into buffer
        void toggleWireframe(); // Toggles wireframe rendering

        void generateShadowMap(AbstractLight *source);

        int addMesh(AbstractMesh *mesh);
        AbstractMesh *getMesh(int meshID);

        int addLight(AbstractLight *light);
        AbstractLight *getLight(int lightID);

        void setCamera(AbstractCamera *camera);
        AbstractCamera *get_camera();

        Shader *getShader();

        void clear();

    protected:

    private:
        Shader m_shader, m_depthShader;

        /* Scene */
        std::vector<AbstractMesh*>  m_meshes;
        std::vector<AbstractLight*> m_lights;

        glm::mat4 m_perspective = glm::mat4(1.0);
        glm::mat4 m_ortho       = glm::mat4(1.0);
        AbstractCamera *m_camera;

        /* OpenGL */
        bool m_wireframe = false;

        struct {
            GLint   cameraPos,
                    projection,
                    camera,
                    modelview,
                    normalMatrix,
                    nbrLights,

                    ambientColor,
                    diffuseColor,
                    specularColor,

                    ambientStrength,
                    diffuseStrength,
                    specularStrength,
                    specularExponent;
        } m_uniformLocations;

        float   m_viewport_width,
                m_viewport_height;
};

#endif // RENDERER_H
