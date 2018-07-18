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

#include "Shader.h"
#include "AbstractMesh.h"

/*!
 * \class Renderer
 * \brief This class takes care of the rendering process for a given list of meshes.
 */
class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();

        void setShader(Shader shader);

        void render(); // Pushes next frame into buffer
        void toggleWireframe(); // Toggles wireframe rendering

        int addMesh(AbstractMesh *mesh);
        AbstractMesh *getMesh(int meshID);


    protected:

    private:
        Shader m_shader;

        /* Scene */
        std::vector<AbstractMesh*> m_meshes;

        glm::mat4 m_projection = glm::mat4(1.0);
        glm::mat4 m_global_modelview = glm::mat4(1.0); // Set as identity by default

        /* OpenGL */
        bool m_wireframe = false;
};

#endif // RENDERER_H
