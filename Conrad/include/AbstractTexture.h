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
        inline void linkToFBO(GLuint fbo, int index = 0) {
            /* index is the attachment index within the FBO */
            glBindRenderbuffer(GL_RENDERBUFFER, fbo);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, m_id, 0);

            // TODO : Unbind the FBO ? Warning, if used with a bind before, unbinding here could be unexpected
        }

        /* OpenGL */
        void bind();
        void unbind();

        /* Setters */
        void setID(GLuint id);
        void setPath(std::string filepath);

        /* Getters */
        GLuint getID();
        bool isLoaded();

    protected:
        static SDL_Surface *reverse_SDL_surface(SDL_Surface *source);

    private:
        std::string m_filepath;

        /* OpenGL */
        GLuint m_id = 0; // 0 is always unused

        bool m_filemode = false;
        bool m_loaded = false;
};

#endif // ABSTRACTTEXTURE_H
