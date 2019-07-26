#ifndef GUIRENDERER_H
#define GUIRENDERER_H

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

class GUIRenderer
{
    public:
        GUIRenderer();
        virtual ~GUIRenderer();

        void load();

        void addGUIObject(AbstractGUIObject *object);

        void render();
        void clear();
    protected:

    private:
        /* Datas */
        // NOTE : Only one VAO/VBO buffer is used per GUIRenderer
        int m_vaoID, m_vboID;

        std::vector<AbstractGUIObject *> m_guiObjects;
};

#endif // GUIRENDERER_H
