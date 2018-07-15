#ifndef RENDERER_H
#define RENDERER_H

#include "Shader.h"

class Renderer
{
    public:
        Renderer();
        virtual ~Renderer();



    protected:

    private:
        Shader m_shader;
};

#endif // RENDERER_H
