#include "AbstractTexture.h"

using namespace std;

AbstractTexture::AbstractTexture() :
    m_mode(INVALID_MODE)
{

}

AbstractTexture::AbstractTexture(string filepath) :
    m_filepath(filepath), m_mode(FILE_MODE)
{

}

void AbstractTexture::setID(GLuint id)
{
    m_mode = FBO_MODE;
    m_id = id;
}

void AbstractTexture::setPath(string filepath)
{
    m_mode = FILE_MODE;
    m_filepath = filepath;
}

void AbstractTexture::setSize(GLsizei width, GLsizei height)
{
    m_width = width;
    m_height = height;
}

bool AbstractTexture::update(SDL_Surface *sdl_image, bool reverse)
{
    if(!m_loaded) {
        return false;
    }
}

bool AbstractTexture::loadFromSDL(SDL_Surface *surface, GLvoid* &data_ptr, GLenum &internalFormat, GLenum &format, bool reverse)
{
    m_mode = SDL_MODE;

    if(surface == 0) {
        cout << "Error while loading texture : " << SDL_GetError() << endl;
        return false;
    }

    SDL_Surface *SDL_image = 0;
    if(reverse) {
        SDL_image = AbstractTexture::reverse_SDL_surface(surface); // Need to reverse the image as OpenGL uses a different coords system for 2D textures.
        SDL_FreeSurface(surface);
    } else {
        SDL_image = surface;
    }

    /* Getting image format */
        if(SDL_image->format->BytesPerPixel == 3) {
            internalFormat = GL_SRGB; // S for gamma correction canceling on the image (it's taken care of in the shader)
            if(SDL_image->format->Rmask == 0xff) { // Red first in the mask
                format = GL_RGB;
            } else {
                format = GL_BGR;
            }
        }

        else if(SDL_image->format->BytesPerPixel == 4) {
            internalFormat = GL_SRGB_ALPHA; // Not GL_RGBA for gamma correction canceling on the image (it's taken care of in the shader)
            if(SDL_image->format->Rmask == 0xff) { // Red first
                format = GL_RGBA;
            } else {
                format = GL_BGRA;
            }
        }

        else { /* Format not recognized */
            cout << "Error while loading texture : format not recognized." << endl;
            return false;
        }

    m_width = SDL_image->w;
    m_height = SDL_image->h;
    data_ptr = (GLvoid *) SDL_image->pixels;

    SDL_FreeSurface(SDL_image);

    return true;
}

bool AbstractTexture::load()
{
    if(m_mode == INVALID_MODE) {
        return false;
    }

    GLvoid *data_ptr = 0; // Blank by default
    m_internalFormat = GL_SRGB_ALPHA;
    m_format = GL_RGBA;

    /* OpenGL texture generation */
    if(glIsTexture(m_id) == GL_TRUE) {
        glDeleteTextures(1, &m_id);
    } glGenTextures(1, &m_id); // Texture ID generation

    SDL_Surface *SDL_image = 0; // Temporary pointer for freeing afterwards
    if(m_mode == FILE_MODE) {
        SDL_Surface *source = IMG_Load(m_filepath.c_str());
        if(!loadFromSDL(source, data_ptr, m_internalFormat, m_format, true)) {
            return false;
        }
    }

    /* Setting up texture */
    glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data_ptr);

        // Filters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    m_loaded = true;
    return true;
}

GLuint AbstractTexture::getID()
{
    return m_id;
}

bool AbstractTexture::isLoaded()
{
    return m_loaded;
}

void AbstractTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void AbstractTexture::unbind() // Could be static (and inline)
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
