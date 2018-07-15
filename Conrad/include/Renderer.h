#ifndef RENDERER_H
#define RENDERER_H

/*!
 * \file Renderer.h
 * \author ThomRI
 * \version 0.1
 */

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
        Renderer();
        virtual ~Renderer();



    protected:

    private:
        Shader m_shader;
};

#endif // RENDERER_H
