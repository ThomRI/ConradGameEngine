#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H

/* Cross-plateform includes */
#ifdef WIN32
    #include <GL/glew.h>

#elif __APPLE__
    #define GL3_PROTOTYPES 1
    #include <OpenGL/gl3.h>

#else // UNIX / Linux
    #define GL3_PROTOTYPES 1
    #include <GL3/gl3.h>

#endif

#include "scope.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class AbstractTexture
{
    public:
        AbstractTexture();
        AbstractTexture(std::string filepath);
        virtual ~AbstractTexture();

        bool load();

        /* OpenGL */
        void bind();
        void unbind();

        /* Setters */
        void setPath(std::string filepath);

        /* Getters */
        GLuint getID();

    protected:
        static SDL_Surface *reverse_SDL_surface(SDL_Surface *source);

    private:
        std::string m_filepath;

        /* OpenGL */
        GLuint m_id;
};

#endif // ABSTRACTTEXTURE_H
