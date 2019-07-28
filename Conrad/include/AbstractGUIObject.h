#ifndef ABSTRACTGUIOBJECT_H
#define ABSTRACTGUIOBJECT_H

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class AbstractGUIObject
{
    public:
        AbstractGUIObject();
        AbstractGUIObject(float *vertices, float *texCoords, int coordsCount); // coordsCount is the number of 2D coordinates (not component!)
        virtual ~AbstractGUIObject();

        virtual void draw() = 0; // Virtual pure

        void setData(float *vertices, float *texCoors, int coordsCount);

        void setPosition(float x, float y);
        void setPosition(glm::vec2 position);
        glm::vec2 getPosition();

        void translate(float x, float y);
        void translate(glm::vec2 vector);

        void scale(float x, float y);
        void scale(float coefficient);

        void rotate(float angle);

        float *getVertices();
        float *getTexCoords();
        int getCoordsCount();

        glm::mat4 &getModelview();

    protected:

    private:
        glm::mat4 m_modelview = glm::mat4(); // set to identity by default

        float *m_vertices;
        float *m_texCoords;
        int m_coordsCount; // 2D vectors !

};

#endif // ABSTRACTGUIOBJECT_H
