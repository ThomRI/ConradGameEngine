#ifndef SHADER_H
#define SHADER_H

#include "scope.h"

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

#include <fstream>
#include <iostream>
#include <string>

class Shader
{
    public:
        Shader();
        Shader(std::string vertexPath, std::string fragmentPath);
        virtual ~Shader();

        void setVertexPath(std::string vertexPath);
        void setFragmentPath(std::string fragmentPath);
        void setPaths(std::string vertexPath, std::string fragmentPath);

        bool load();

        /* Getters */
        GLuint getProgramID();
        GLuint getVertexShaderID();
        GLuint getFragmentShaderID();

        std::string getVertexPath() const;
        std::string getFragmentPath() const;

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
