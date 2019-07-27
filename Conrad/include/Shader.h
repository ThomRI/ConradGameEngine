#ifndef SHADER_H
#define SHADER_H

#include "scope.h"

/* GLM */
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
        Shader(std::string vertexPath, std::string fragmentPath, std::string geometryPath);
        virtual ~Shader();

        void setVertexPath(std::string vertexPath);
        void setFragmentPath(std::string fragmentPath);
        void setGeometryPath(std::string geometryPath);

        bool load();

        void bind();
        static inline void unbind() { glUseProgram(0); };

        inline GLint getUniformLocation(const GLchar *name) const       { return glGetUniformLocation(m_programID, name); };

        /* Uniform sends */
        static inline void sendVector(GLint location, glm::vec2 vector) { glUniform2f(location, vector[0], vector[1]); };
        static inline void sendVector(GLint location, glm::vec3 vector) { glUniform3f(location, vector[0], vector[1], vector[2]); };
        static inline void sendRGB(GLint location, RGB color)           { glUniform3f(location, color.r, color.g, color.b); };

        static inline void sendMatrix(GLint location, glm::mat3 matrix) { glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); };
        static inline void sendMatrix(GLint location, glm::mat4 matrix) { glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix)); };

        static inline void sendFloat(GLint location, float value)       { glUniform1f(location, value); };
        static inline void sendInt(GLint location, int value)           { glUniform1i(location, value); };
        static inline void sendBool(GLint location, bool value)         { glUniform1i(location, value); };

        /* Getters */
        GLuint getProgramID();
        GLuint getVertexShaderID();
        GLuint getFragmentShaderID();

        std::string getVertexPath() const;
        std::string getFragmentPath() const;

    protected:
        static bool compile(GLuint &id, GLenum type, std::string const path);

    private:
        GLuint  m_vertexID      = 0,
                m_fragmentID    = 0,
                m_geometryID    = 0,
                m_programID     = 0;

        std::string m_vertexPath,
                    m_fragmentPath,
                    m_geometryPath;

        bool m_usesGeometryShader = false;
};

#endif // SHADER_H
