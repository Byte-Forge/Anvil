//
// Created by stephan on 28.10.15.
//

#include "Shader.hpp"
#include "flextGL.h"
#include <fstream>
#include <iostream>
using namespace hpse;

GL::Shader::Shader()
{
    m_program = glCreateProgram();
}

GL::Shader::~Shader()
{
    for(const auto& p : m_shaders)
    {
        glDeleteShader(p.second);
    }

    glDeleteProgram(m_program);
}

void GL::Shader::Load(const std::string &vertShader, const std::string &fragShader)
{
    LoadShader(vertShader, GL_VERTEX_SHADER);
    LoadShader(fragShader, GL_FRAGMENT_SHADER);
}

void GL::Shader::Load(const std::string &vertShader, const std::string& geoShader, const std::string &fragShader)
{
    LoadShader(vertShader, GL_VERTEX_SHADER);
    LoadShader(geoShader, GL_GEOMETRY_SHADER);
    LoadShader(fragShader, GL_FRAGMENT_SHADER);
}

void GL::Shader::LoadShader(const std::string file, GLenum type)
{
    std::ifstream fin(file);
    if(fin.fail())
    {
        std::cout << "Failed to load Shader: " << file << std::endl;
    }

    fin.seekg(0,std::ios::end);
    auto size = fin.tellg();
    fin.seekg(0,std::ios::beg);

    char* buffer = new char[size];
    fin.read(buffer,size);
    delete[] buffer;

    if(m_shaders[type])
    {
        glDeleteShader(m_shaders[type]);
    }

    m_shaders[type] = glCreateShader(type);
    const auto& shader = m_shaders[type];
    glShaderSource(shader,1,&buffer,NULL);
}

void GL::Shader::Bind()
{
    glUseProgram(m_program);
}

void GL::Shader::Compile()
{
    for(auto& p : m_shaders)
    {
        glCompileShader(p.second);
        glAttachShader(m_program,p.second);
    }

    glLinkProgram(m_program);
}