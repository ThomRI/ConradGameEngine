#ifndef SHADER_H
#define SHADER_H

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

/* Defines for VertexAttribPointer IDs */
#define VERTEX_BUFFER   0
#define COLOR_BUFFER    1
#define TEX_BUFFER      2

#include <iostream>
#include <string>

class Shader
{
    public:
        Shader(std::string vertexPath, std::string fragmentPath);
        Shader(Shader const &shader);
        virtual ~Shader();

        bool load();

        /* Getters */
        GLuint getProgramID();
        GLuint getVertexShaderID();
        GLuint getFragmentShaderID();

        /* Operator overload */
        Shader &operator=(Shader const &shader);

    protected:
        static bool compile(GLuint &id, GLenum type, std::string const path);

    private:
        GLuint  m_vertexID,
                m_fragmentID,
                m_programID;

        std::string m_vertexPath,
                    m_fragmentPath;
};

#endif // SHADER_H
