/*
************************************
* Copyright (C) 2016 ByteForge
* Shader.cpp
************************************
*/

#include "Shader.hpp"
#include "flextGL.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "../../Exception.hpp"

using namespace anvil;

const std::string GL::Shader::glslVersion = "400 core";

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

void GL::Shader::Define(const std::string & macro)
{
	m_macros[macro] = std::string();
}

void GL::Shader::Define(const std::string & macro, const std::string & value)
{
	m_macros[macro] = value;
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

    
	int* size = new int[2];
    char** buffer = new char*[2];

	std::string macroStr;
	macroStr += "#version " + glslVersion + "\n";
	for (const auto& m : m_macros)
	{
		macroStr += "#define " + m.first + " " + m.second + "\n";
	}
	
	size[0] = macroStr.size();
	buffer[0] = const_cast<char*>(macroStr.c_str());
	fin.seekg(0, std::ios::end);
	
	size[1] = (int)fin.tellg();
	fin.seekg(0, std::ios::beg);
	buffer[1] = new char[size[1]];
	std::memset(buffer[1], 0, size[1]);
    fin.read(buffer[1], size[1]);

    if(m_shaders[type])
    {
        glDeleteShader(m_shaders[type]);
    }

    m_shaders[type] = glCreateShader(type);
    const auto& shader = m_shaders[type];
    glShaderSource(shader,2,buffer, size);

	delete[] size;
	delete[] buffer[1];
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