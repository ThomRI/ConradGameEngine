#include "Shader.h"

using namespace std;
using namespace glm;

Shader::Shader()
{

}

Shader::Shader(string vertexPath, string fragmentPath) :
    m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{
    m_usesGeometryShader = false;
}

Shader::Shader(string vertexPath, string fragmentPath, string geometryPath) :
    m_vertexPath(vertexPath), m_fragmentPath(fragmentPath), m_geometryPath(geometryPath)
{
    m_usesGeometryShader = true;
}

void Shader::setVertexPath(string vertexPath)
{
    m_vertexPath = vertexPath;
}

void Shader::setFragmentPath(string fragmentPath)
{
    m_fragmentPath = fragmentPath;
}

void Shader::setGeometryPath(string geometryPath)
{
    m_geometryPath = geometryPath;
    m_usesGeometryShader = true;
}

bool Shader::load()
{
    cout << glIsShader(m_vertexID) << endl;
    cout << "Loading shader" << endl;
    /* Deleting a potential former shader with same IDs */
    if(glIsShader(m_vertexID) == GL_TRUE) {
        glDeleteShader(m_vertexID);
    }

    if(glIsShader(m_fragmentID) == GL_TRUE) {
        glDeleteShader(m_fragmentID);
    }

    if(m_usesGeometryShader) {
        if(glIsShader(m_geometryID) == GL_TRUE) {
            glDeleteShader(m_geometryID);
        }
    }

    if(glIsProgram(m_programID) == GL_TRUE) {
        glDeleteProgram(m_programID);
    }

    /* Compiling vertex and fragment shaders */
    if(!Shader::compile(m_vertexID, GL_VERTEX_SHADER, m_vertexPath)) {
        return false;
    }

    if(!Shader::compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentPath)) {
        return false;
    }

    if(m_usesGeometryShader) {
        if(!Shader::compile(m_geometryID, GL_GEOMETRY_SHADER, m_geometryPath)) {
            return false;
        }
    }

    cout << "Compiled correctly" << endl;

    /* Program Creation */
    m_programID = glCreateProgram();
                                glAttachShader(m_programID, m_vertexID);
                                glAttachShader(m_programID, m_fragmentID);
    if(m_usesGeometryShader)    glAttachShader(m_programID, m_geometryID);

    /* VertexAttribPointer IDs (those are universal in the engine */
    glBindAttribLocation(m_programID, VERTEX_BUFFER, "in_Vertex");
    glBindAttribLocation(m_programID, COLOR_BUFFER, "in_Color");
    glBindAttribLocation(m_programID, TEX_BUFFER, "in_TexCoord0"); // Multitexturing isn't supported for now
    glBindAttribLocation(m_programID, VERTEX_NORMAL_BUFFER, "in_VertexNormal");
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
            cout << "Can't open shader file ! (" << path << ")" << endl;
            glDeleteShader(id);
            return false;
        }

        string line, source;
        while(getline(file, line)) {
            source += line + '\n';
        }

        file.close();

    /* Compiling shader */
        const GLchar *source_cstr = source.c_str();
        glShaderSource(id, 1, &source_cstr, 0);
        glCompileShader(id);

    /* Checking compilation */
    GLint status(0);
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if(status != GL_TRUE) { // An error occurred
        GLint errorSize(0);
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorSize);

        char *error = new char[errorSize + 1]; // +1 for EOF (not provided by glGetShaderInfoLog)
        glGetShaderInfoLog(id, errorSize, &errorSize, error);
        error[errorSize] = '\0'; // EOF

        cout << error << endl;

        delete[] error;
        glDeleteShader(id);

        return false;
    }

    return true;
}

void Shader::bind()
{
    glUseProgram(m_programID);
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

string Shader::getVertexPath() const
{
    return m_vertexPath;
}

string Shader::getFragmentPath() const
{
    return m_fragmentPath;
}

Shader::~Shader()
{
    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}
