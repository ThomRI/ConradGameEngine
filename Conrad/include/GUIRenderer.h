#ifndef GUIRENDERER_H
#define GUIRENDERER_H

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "Shader.h"
#include "AbstractGUIObject.h"

class GUIRenderer
{
    public:
        GUIRenderer();
        virtual ~GUIRenderer();

        void load();

        void addGUIObject(AbstractGUIObject *object);
        void setShader(Shader shader);

        void render();
        void clear();
    protected:

    private:
        /* OpenGL */
            // NOTE : Only one VAO/VBO buffer is used per GUIRenderer
            GLuint m_vaoID, m_vboID;

        Shader m_shader;

        std::vector<AbstractGUIObject *> m_guiObjects;
};

#endif // GUIRENDERER_H
