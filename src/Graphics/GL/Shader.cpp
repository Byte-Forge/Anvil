//
// Created by stephan on 28.10.15.
//

#include "Shader.hpp"
#include "flextGL.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
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
		return;
    }

    fin.seekg(0,std::ios::end);
    int size = (int)fin.tellg();
    fin.seekg(0,std::ios::beg);

    char* buffer = new char[size+1];
	std::memset(buffer, 0, size);
    fin.read(buffer,size);


    if(m_shaders[type])
    {
        glDeleteShader(m_shaders[type]);
    }

    m_shaders[type] = glCreateShader(type);
    const auto& shader = m_shaders[type];
    glShaderSource(shader,1,&buffer, &size);
	delete[] buffer;
}

void GL::Shader::Use()
{
    glUseProgram(m_program);
}

void GL::Shader::Compile()
{
	GLint success = 0;
	GLint logLength = 0;

    for(auto& p : m_shaders)
    {
        glCompileShader(p.second);
		glGetShaderiv(p.second, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderiv(p.second, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> errorLog(logLength);
			glGetShaderInfoLog(p.second, logLength, &logLength, &errorLog[0]);
			std::cout << &errorLog[0] << std::endl;
			glDeleteShader(p.second);

		}
		else
			glAttachShader(m_program,p.second);
    }

    glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> errorLog(logLength);
		glGetProgramInfoLog(m_program, logLength, &logLength, &errorLog[0]);
		std::cout << &errorLog[0] << std::endl;
		glDeleteProgram(m_program);
	}

	for (auto& p : m_shaders)
	{
		glDetachShader(m_program, p.second);
	}
}