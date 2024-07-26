#include "shader.h"


std::string readFile(const char *path)
{
    std::ifstream file{ path };
    assert(file.is_open());

    std::stringstream returnValue;
    std::string line;
    while(getline(file, line))
        returnValue << line << "\n";
    
    return returnValue.str();
}
int checkShaderError(const char *shader_name, unsigned int shader_id)
{
    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* infoLog = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader_id, length, &length, infoLog);
        std::cout << shader_name << " failed to compile!" << "\n";
        std::cout << "Reason: " << infoLog << "\n";
        glDeleteShader(shader_id);

        return 0;
    }

    return 1;
}


ShaderProgram::ShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path)
{
    m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_VertexShader = readFile(vertex_shader_path);
    const char *vertexShader = m_VertexShader.c_str();
    glShaderSource(m_VertexShaderID, 1, &vertexShader, nullptr);
    glCompileShader(m_VertexShaderID);
    assert(checkShaderError("Vertex Shader", m_VertexShaderID));
    
    m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    m_FragmentShader = readFile(fragment_shader_path);
    const char *fragmentShader = m_FragmentShader.c_str();
    glShaderSource(m_FragmentShaderID, 1, &fragmentShader, nullptr);
    glCompileShader(m_FragmentShaderID);
    assert(checkShaderError("Fragment Shader", m_FragmentShaderID));

    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, m_VertexShaderID);
    glAttachShader(m_ProgramID, m_FragmentShaderID);
    glLinkProgram(m_ProgramID);
    glValidateProgram(m_ProgramID);
}

unsigned int ShaderProgram::getProgramID() { return m_ProgramID; }
unsigned int ShaderProgram::getVertexShaderID() { return m_VertexShaderID; }
unsigned int ShaderProgram::getFragmentShaderID() { return m_FragmentShaderID; }

void ShaderProgram::bind() { glUseProgram(m_ProgramID); }

ShaderProgram::~ShaderProgram()
{
    glDetachShader(m_ProgramID, m_VertexShaderID);
    glDeleteShader(m_VertexShaderID);
    
    glDetachShader(m_ProgramID, m_FragmentShaderID);
    glDeleteShader(m_FragmentShaderID);

    glDeleteProgram(m_ProgramID);
}
