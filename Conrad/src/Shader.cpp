#include "Shader.h"

using namespace std;

Shader::Shader()
{
    cout << "Default constructor" << endl;
}

Shader::Shader(string vertexPath, string fragmentPath) :
    m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{
    cout << "String constructor" << endl;
}

void Shader::setVertexPath(string vertexPath)
{
    m_vertexPath = vertexPath;
}

void Shader::setFragmentPath(string fragmentPath)
{
    m_fragmentPath = fragmentPath;
}

void Shader::setPaths(string vertexPath, string fragmentPath)
{
    m_vertexPath = vertexPath;
    m_fragmentPath = fragmentPath;
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


    cout << "Compiling " << m_vertexPath << endl;
    /* Compiling vertex and fragment shaders */
    if(!Shader::compile(m_vertexID, GL_VERTEX_SHADER, m_vertexPath)) {
        cout << "Error compiling a VERTEX_SHADER. (" << m_vertexPath << ")" << endl;
        return false;
    }

    cout << "Compiling " << m_fragmentPath << endl;
    if(!Shader::compile(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentPath)) {
        cout << "Error compiling a FRAGMENT_SHADER." << endl;
        return false;
    }

    /* Program Creation */
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);

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
            cout << "Can't open file !" << endl;
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
