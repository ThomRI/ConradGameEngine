#ifndef SIMPLETEXTUREGUI_H
#define SIMPLETEXTUREGUI_H

#include "AbstractTexture.h"
#include "AbstractGUIObject.h"

class SimpleTextureGUI : public AbstractGUIObject
{
    public:
        SimpleTextureGUI(AbstractTexture *texture);
        virtual ~SimpleTextureGUI();

        void draw();

    protected:

    private:
        AbstractTexture *m_texture;
};

#endif // SIMPLETEXTUREGUI_H
