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

std::map<IShader::ShaderType, GLenum> GL::Shader::s_mapping = {
	{ IShader::ANVIL_VERT_SHADER, GL_VERTEX_SHADER },
	{ IShader::ANVIL_TESC_SHADER, GL_TESS_CONTROL_SHADER },
	{ IShader::ANVIL_TESE_SHADER, GL_TESS_EVALUATION_SHADER },
	{ IShader::ANVIL_GEOM_SHADER, GL_GEOMETRY_SHADER },
	{ IShader::ANVIL_FRAG_SHADER, GL_FRAGMENT_SHADER },
};

GL::Shader::Shader() : IShader()
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


void GL::Shader::LoadShader(const std::string& file, const ShaderType type)
{
	GLint success = 0;
	GLint logLength = 0;

    std::ifstream fin(file);
    if(fin.fail())
		throw AnvilException("Failed to load shader " + file, __FILE__, __LINE__);
	
	IShader::LoadShader(file, type);

	const GLenum gl_type = s_mapping[type];
	int size = 0;
	fin.seekg(0, std::ios::end);	
	size = (int)fin.tellg();
	fin.seekg(0, std::ios::beg);
	char* buffer = new char[size];
	std::memset(buffer, 0, size);
    fin.read(buffer, size);

	GLuint shader = glCreateShader(gl_type);
	glShaderSource(shader, 1, &buffer, &size);

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);
		std::cout << &errorLog[0] << std::endl;
		glDeleteShader(shader);
	}
	else
	{
		glAttachShader(m_program, shader);
		m_shaders[gl_type] = shader;
	}
		
	if(buffer)
		delete[] buffer;
}

void GL::Shader::Use()
{
	IShader::Ready();
    glUseProgram(m_program);
	//bind its ubos
	for (auto index : m_ubos)
		glBindBufferBase(GL_UNIFORM_BUFFER, index.second, index.second);
}

int GL::Shader::GetUniform(const std::string &name)
{
	const auto& it = m_uniforms.find(name);
	if (it == m_uniforms.end())
	{
		const GLint loc = glGetUniformLocation(m_program, name.c_str());
		/*if (loc == -1)
			throw AnvilException("Uniform: \"" + name + "\" doesn't exist!", __FILE__, __LINE__);
		*/
		m_uniforms[name] = loc;
	}	
	return m_uniforms[name];
}

int GL::Shader::GetUniformBuffer(const std::string &name)
{
	const auto& it = m_ubos.find(name);
	if (it == m_ubos.end())
	{
		const GLint loc = glGetUniformBlockIndex(m_program, name.c_str());
		/*if (loc == -1)
			throw AnvilException("Uniform buffer: \"" + name + "\" doesn't exist!", __FILE__, __LINE__);*/
		m_ubos[name] = loc;
	}
	return m_ubos[name];
}

void GL::Shader::Link()
{
	GLint success = 0;
	GLint logLength = 0;

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

	GLsizei count;
	GLuint attached[5];
	glGetAttachedShaders(m_program, 5, &count, attached);

	for(int i=0; i<count; ++i)
	{
		glDetachShader(m_program, attached[i]);
		glDeleteShader(attached[i]);
	}
}

void GL::Shader::AttachUBO(const std::string& name, int id)
{
	glUniformBlockBinding(m_program, GetUniformBuffer(name), id);
	m_ubo_indices[name] = id;
	m_ubos[name] = id; //why do we need this ??? or why does this even work?^^
}
