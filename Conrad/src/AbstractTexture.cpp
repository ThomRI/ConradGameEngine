#include "AbstractTexture.h"

using namespace std;

AbstractTexture::AbstractTexture()
{
    //ctor
}

AbstractTexture::AbstractTexture(string filepath) :
    m_filepath(filepath)
{

}

void AbstractTexture::setPath(string filepath)
{
    m_filepath = filepath;
}

bool AbstractTexture::load()
{
    SDL_Surface *source = IMG_Load(m_filepath.c_str());

    if(source == 0) {
        cout << "Error while loading texture (" << m_filepath << ") : " << SDL_GetError() << endl;
        return false;
    }
    SDL_Surface *SDL_image = AbstractTexture::reverse_SDL_surface(source); // Need to reverse the image as OpenGL uses a different coords system for 2D textures.
    SDL_FreeSurface(source);

    /* OpenGL texture generation */
    if(glIsTexture(m_id) == GL_TRUE) {
        glDeleteTextures(1, &m_id);
    } glGenTextures(1, &m_id); // Texture ID generation

    /* Getting image format */
        GLenum internalFormat(0), format(0);
        if(SDL_image->format->BytesPerPixel == 3) {
            internalFormat = GL_RGB;
            if(SDL_image->format->Rmask == 0xff) { // Red first in the mask
                format = GL_RGB;
            } else {
                format = GL_BGR;
            }
        }

        else if(SDL_image->format->BytesPerPixel == 4) {
            internalFormat = GL_RGBA;
            if(SDL_image->format->Rmask == 0xff) { // Red first
                format = GL_RGBA;
            } else {
                format = GL_BGRA;
            }
        }

        else { /* Format not recognized */
            cout << "Error while loading texture (" << m_filepath << ") : format not recognized." << endl;
            return false;
        }

    /* Setting up texture */
    glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, SDL_image->w, SDL_image->h, 0, format, GL_UNSIGNED_BYTE, SDL_image->pixels);

        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(SDL_image);
    return true;
}

GLuint AbstractTexture::getID()
{
    return m_id;
}

void AbstractTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void AbstractTexture::unbind() // Could be static
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

SDL_Surface *AbstractTexture::reverse_SDL_surface(SDL_Surface *source)
{
    SDL_Surface *reversed = SDL_CreateRGBSurface(0,
                                                 source->w,
                                                 source->h,
                                                 source->format->BitsPerPixel,
                                                 source->format->Rmask,
                                                 source->format->Gmask,
                                                 source->format->Bmask,
                                                 source->format->Amask);

    // Pointers to pixels array
    unsigned char* sourcePixels = (unsigned char*) source->pixels;
    unsigned char* reversedPixels = (unsigned char*) reversed->pixels;

    int row = source->w * source->format->BytesPerPixel;
    for(int y = 0;y < source->h; y++) {
        for(int x = 0; x < row; x++) {
            reversedPixels[(source->h - 1 - y) * row + x] = sourcePixels[y * row + x];
        }
    }

    return reversed;
}

AbstractTexture::~AbstractTexture()
{
    glDeleteTextures(1, &m_id);
}
