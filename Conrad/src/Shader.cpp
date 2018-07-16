#include "Shader.h"

using namespace std;

Shader::Shader(string vertexPath, string fragmentPath) :
    m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{

}

Shader::Shader(Shader const &shader)
{
    m_vertexPath = shader.m_vertexID;
    m_fragmentPath = shader.m_fragmentPath;
}

bool Shader::load()
{
    /* Deleting a potential former shader with same IDs */
    if(glIsShader(m_vertexID) == GL_TRUE) {
        glDeleteShader(m_vertexID);
    }

    if(glIsShader(m_fragmentID) == GL_TRUE) {
        glDeleteShader(m_fragmentID);
    }

    if(glIsProgram(m_programID) == GL_TRUE) {
        glDeleteProgram(m_programID);
    }


    /* Compiling vertex and fragment shaders */
    if(!Shader::compile(m_vertexID, GL_VERTEX_SHADER, m_vertexPath)) {
        cout << "Error compiling a VERTEX_SHADER." << endl;
        return false;
    }

    if(!Shader::compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentPath)) {
        cout << "Error compiling a FRAGMENT_SHADER." << endl;
        return false;
    }

    /* Program Creation */
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_progamID, m_fragmentID);

    /* VertexAttribPointer IDs (those are universal in the engine */
    glBindAttribLocation(m_programID, VERTEX_BUFFER, "in_Vertex");
    glBindAttribLocation(m_programID, COLOR_BUFFER, "in_Color");
    glBindAttribLocation(m_programID, TEX_BUFFER, "in_TexCoord0"); // Multitexturing isn't supported for now
    // TODO : Add multitexturing

    /* Linking */
        glLinkProgram(m_programID);

        GLint linkingStatus(0);
        glGetProgramiv(m_programID, GL_LINK_STATUS, &linkingStatus);

        if(linkingStatus != GL_TRUE) { // An error occurred
            GLint errorSize(0);
            glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &errorSize);

            char *error = new char[errorSize + 1];
            glGetShaderInfoLog(m_programID, errorSize, &errorSize, error);
            error[errorSize] += '\0';

            cout << error << endl;

            delete[] error;
            glDeleteProgram(m_programID);

            return false;
        }

    return true;
}

bool Shader::compile(GLuint &id, GLenum type, string const path)
{
    id = glCreateShader(type);
    if(id == 0) {
        return false;
    }

    /* Loading file */
        ifstream file(path.c_str());
        if(!file) {
            glDeleteShader(id);
            return false;
        }

        string line, source;
        while(getline(file, line)) {
            source += line + '\n';
        }

        file.close();

    /* Compiling shader */
        glShaderSource(id, 1, &(source.c_str()), 0);
        glCompileShader(id);

    /* Checking compilation */
    GLint status(0);
    glGetShaderiv(id, GL_COMPILE_STATUS, &error);

    if(status != GL_TRUE) { // An error occurred
        GLint errorSize(0);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorSize);

        char *error = new char[errorSize + 1]; // +1 for EOF (not provided by glGetShaderInfoLog)
        glGetShaderInfoLog(id, errorSize, &errorSier, error);
        error[errorSize] = '\0'; // EOF

        cout << error << endl;

        delete[] error;
        glDeleteShader(id);

        return false;
    }

    return true;
}

GLuint Shader::getProgramID()
{
    return m_programID;
}

GLuint Shader::getVertexShaderID()
{
    return m_vertexID;
}

GLuint Shader::getFragmentShaderID()
{
    return m_fragmentID;
}

Shader &Shader::operator=(Shader const &shader)
{
    m_vertexPath = shader.m_vertexPath;
    m_fragmentPath = shader.m_fragmentPath;

    load();

    return *this;
}

Shader::~Shader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}
