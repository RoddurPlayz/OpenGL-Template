#pragma once


#include <iostream>
#include <assert.h>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>

#include <GL/glew.h>


std::string readFile(const char *path);
int checkShaderError(const char *shader_name, unsigned int shader_id);


class ShaderProgram
{
private:
    unsigned int m_VertexShaderID;
    std::string m_VertexShader;

    unsigned int m_FragmentShaderID;
    std::string m_FragmentShader;

    unsigned int m_ProgramID;
public:
    ShaderProgram(const char *vertex_shader_path, const char *fragment_shader_path);

    unsigned int getProgramID();
    unsigned int getVertexShaderID();
    unsigned int getFragmentShaderID();

    void bind();

    ~ShaderProgram();
};
