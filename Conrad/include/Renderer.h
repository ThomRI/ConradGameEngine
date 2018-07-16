#ifndef RENDERER_H
#define RENDERER_H

/*!
 * \file Renderer.h
 * \author ThomRI
 * \version 0.1
 */

#include <vector>

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"

/* Defines a byte offset from an index offset */
#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + offset)
#endif

/*!
 * \class Renderer
 * \brief This class takes care of the rendering process for a given list of meshes.
 */
class Renderer
{
    public:
        Renderer(Shader shader);
        virtual ~Renderer();

        void render(); // Pushes next frame into buffer

        int addMesh(AbstractMesh *mesh);
        AbstractMesh *getMesh(int meshID);

    protected:

    private:
        Shader m_shader;

        /* Scene */
        std::vector<*AbstractMesh> m_meshes;

        glm::mat4 m_projection = mat4(1.0);
        glm::mat4 m_global_modelview = mat4(1.0); // Set as identity by default
};

#endif // RENDERER_H
