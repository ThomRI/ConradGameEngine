#include "SimpleTextureGUI.h"

using namespace std;

SimpleTextureGUI::SimpleTextureGUI(AbstractTexture *texture) :
    AbstractGUIObject(), m_texture(texture)
{
    float vertices[12] = {   -1.0, 1.0,      1.0, -1.0,       1.0, 1.0,
                            -1.0, 1.0,      -1.0, -1.0,     1.0, -1.0}; // 2 triangles

    float tex[12] = {0.0, 0.0,       1.0, 0.0,       1.0, 1.0,
                    0.0, 0.0,       0.0, 1.0,       1.0, 1.0};

    setData(vertices, tex, 6);
}

void SimpleTextureGUI::draw()
{
    m_texture->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    m_texture->unbind();
}

SimpleTextureGUI::~SimpleTextureGUI()
{
    //dtor
}
