#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

/*!
 *  \file AbstractMaterial.h
 *  \author ThomRI
 */

 #include "scope.h" // RGB structure
 #include "AbstractTexture.h"

/*!
 *  \class AbstractMaterial
 *  \brief Defines a basic material (ambient, diffuse, specular, emit)
 */
class AbstractMaterial
{
    public:
        AbstractMaterial();
        AbstractMaterial(RGB ambient, RGB diffuse, RGB specular, RGB emit, float specularExponent, float alpha, float ambientStrength = 0.1, float diffuseStrength = 1.0, float specularStrength = 1.0, float emitStrength = 1.0);
        virtual ~AbstractMaterial();

        /* Getters */
        RGB getAmbientColor();
        RGB getDiffuseColor();
        RGB getSpecularColor();
        RGB getEmitColor();

        float getAmbientStrength();
        float getDiffuseStrength();
        float getSpecularStrength();
        float getEmitStrength();

        float getSpecularExponent();
        float getAlpha();

        AbstractTexture *getDiffuseTexture();
        AbstractTexture *getSpecularTexture();

        bool isDiffuseTextured();
        bool isSpecularTextured();

        /* Setters */
        void setAmbientColor(RGB color);
        void setAmbientColor(float r, float g, float b);

        void setDiffuseColor(RGB color);
        void setDiffuseColor(float r, float g, float b);

        void setSpecularColor(RGB color);
        void setSpecularColor(float r, float g, float b);

        void setEmitColor(RGB color);
        void setEmitColor(float r, float g, float b);

        void setAmbientStrength(float strength);
        void setDiffuseStrength(float strength);
        void setSpecularStrength(float strength);
        void setEmitStrength(float strength);

        void setSpecularExponent(float exponent);
        void setAlpha(float alpha);

        void setDiffuseTexture(AbstractTexture *texture);
        void setSpecularTexture(AbstractTexture *texture);


    protected:

    private:
        /* Values */
        RGB     m_ambientColor   = RGB(0.0, 0.0, 0.0),
                m_diffuseColor   = RGB(0.0, 0.0, 0.0),
                m_specularColor  = RGB(0.0, 0.0, 0.0),
                m_emitColor      = RGB(0.0, 0.0, 0.0);

        float   m_ambientStrength   = 0.1,
                m_diffuseStrength   = 1.0,
                m_specularStrength  = 1.0,
                m_emitStrength      = 1.0;


        float   m_specularExponent = 0,
                m_alpha = 1;

        /* Textures */
        AbstractTexture *m_diffuseTexture,
                        *m_specularTexture;

        bool    m_diffuseTextured = false,
                m_specularTextured = false;
};

#endif // ABSTRACTMATERIAL_H
