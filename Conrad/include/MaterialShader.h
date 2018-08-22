#ifndef MATERIALSHADER_H
#define MATERIALSHADER_H

/*!
 *  \file MaterialShader.h
 */

#include "Shader.h"

/*!
 *  \class MaterialShader
 *  \brief Shader specialization. Is capable of handling colors, textures, non-cube shadow maps and basic lighting
 */
class MaterialShader : public Shader
{
    public:
        MaterialShader();
        virtual ~MaterialShader();

    protected:

    private:

};

#endif // MATERIALSHADER_H
