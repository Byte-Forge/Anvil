/*
************************************
* Copyright (C) 2016 ByteForge
* Shader.cpp
************************************
*/

#include "ShaderGL.hpp"
#include "flextGL.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "../../Exception.hpp"

using namespace anvil;

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

void GL::Shader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader)
{
	LoadShader(vertShader, GL_VERTEX_SHADER);
	LoadShader(tessControlShader, GL_TESS_CONTROL_SHADER);
	LoadShader(tessEvalShader, GL_TESS_EVALUATION_SHADER);
	LoadShader(fragShader, GL_FRAGMENT_SHADER);
}

void GL::Shader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader)
{
	LoadShader(vertShader, GL_VERTEX_SHADER);
	LoadShader(tessControlShader, GL_TESS_CONTROL_SHADER);
	LoadShader(tessEvalShader, GL_TESS_EVALUATION_SHADER);
	LoadShader(geoShader, GL_GEOMETRY_SHADER);
	LoadShader(fragShader, GL_FRAGMENT_SHADER);
}


void GL::Shader::LoadShader(const std::string& file, GLenum type)
{
    std::ifstream fin(file);
    if(fin.fail())
		throw AnvilException("Failed to load shader " + file, __FILE__, __LINE__);
	
	std::cout << file << std::endl;
	int size = 0;
	fin.seekg(0, std::ios::end);	
	size = (int)fin.tellg();
	fin.seekg(0, std::ios::beg);
	char* buffer = new char[size];
	std::memset(buffer, 0, size);
    fin.read(buffer, size);

    if(m_shaders[type])
    {
        glDeleteShader(m_shaders[type]);
    }

    m_shaders[type] = glCreateShader(type);
    const auto& shader = m_shaders[type];
    glShaderSource(shader,1,&buffer, &size);

	if(buffer)
		delete[] buffer;
}

void GL::Shader::Use()
{
    glUseProgram(m_program);
}

int GL::Shader::GetUniform(const std::string &name)
{
	const auto& it = m_uniforms.find(name);
	if (it == m_uniforms.end())
	{
		const GLint loc = glGetUniformLocation(m_program, name.c_str());
		if (loc == -1)
			throw AnvilException("Uniform: \"" + name + "\" doesn't exist!", __FILE__, __LINE__);
		m_uniforms[name] = loc;
		return loc;
	}
		
	return it->second;
}

int GL::Shader::GetUniformBuffer(const std::string &name, int index)
{
	const auto& it = m_ubos.find(name);
	if (it == m_ubos.end())
	{
		const GLint loc = glGetUniformBlockIndex(m_program, name.c_str());
		if (loc == -1)
			throw AnvilException("Uniform buffer: \"" + name + "\" doesn't exist!", __FILE__, __LINE__);
		m_ubos[name] = loc;
		glUniformBlockBinding(m_program, index, loc);
		return loc;
	}
		
	return it->second;
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

