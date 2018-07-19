#ifndef ABSTRACTMATERIAL_H
#define ABSTRACTMATERIAL_H

/*!
 *  \file AbstractMaterial.h
 *  \author ThomRI
 */

#include "utilities.hpp"

/*!
 *  \class AbstractMaterial
 *  \brief Defines a basic material (ambient, diffuse, specular, emit)
 */
class AbstractMaterial
{
    public:
        AbstractMaterial();
        AbstractMaterial(RGB ambient, RGB diffuse, RGB specular, RGB emit, float m_specularExponent, float m_alpha);
        virtual ~AbstractMaterial();

        /* Getters */
        RGB ambient();
        RGB diffuse();
        RGB specular();
        RGB emit();
        float specularExponent();
        float alpha();

        /* Setters */
        void setAmbient(RGB ambient);
        void setAmbient(float r, float g, float b);

        void setDiffuse(RGB diffuse);
        void setDiffuse(float r, float g, float b);

        void setSpecular(RGB specular);
        void setSpecular(float r, float g, float b);

        void setEmit(RGB emit);
        void setEmit(float r, float g, float b);

        void setSpecularExponent(float exponent);
        void setAlpha(float alpha);


    protected:

    private:
        /* Values */
        RGB     m_ambient   = {0, 0, 0},
                m_diffuse   = {0, 0, 0},
                m_specular  = {0, 0, 0},
                m_emit      = {0, 0, 0};

        float   m_specularExponent = 0,
                m_alpha = 1;
};

#endif // ABSTRACTMATERIAL_H
