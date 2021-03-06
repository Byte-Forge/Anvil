/*
************************************
* Copyright (C) 2016 ByteForge
* MeshGL.cpp
************************************
*/

#include "MeshGL.hpp"
#include <iostream>
#include "../IShader.hpp"

using namespace anvil;

GL::MeshGL::MeshGL() : m_vao(0)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_vbo->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_uvbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_uvbo->Bind();
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_nbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_nbo->Bind();

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_fbo = std::make_unique<GL::Buffer>(ELEMENT_ARRAY_BUFFER);
	m_fbo->Bind();

	glBindVertexArray(0);
}

GL::MeshGL::~MeshGL()
{
	if (m_vao)
	{
		glDeleteVertexArrays(1, &m_vao);
		m_vao = 0;
	}
}

size_t GL::MeshGL::Render(IShader& shader, bool minimal)
{
	glUniform1i(shader.GetUniform("meshType"), m_type);
	glUniform1i(shader.GetUniform("parentPivot"), m_parentPivot);
	glBindVertexArray(m_vao);
	m_fbo->Bind();

	if (minimal)
	{
		glDrawElements(GL_TRIANGLES, (GLsizei)m_faces.size() * 3, GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		//used for tesselation
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawElements(GL_PATCHES, (GLsizei)m_faces.size() * 3, GL_UNSIGNED_INT, nullptr);
	}

	glBindVertexArray(0);

	return m_faces.size();
}

void GL::MeshGL::Init()
{
	glBindVertexArray(m_vao);
	m_vbo->Update(sizeof(glm::f32vec3) * m_vertices.size(), m_vertices.data());

	m_nbo->Update(sizeof(glm::f32vec3) * m_normals.size(), m_normals.data());

	m_uvbo->Update(sizeof(glm::f32vec2) * m_uvCoords.size(), m_uvCoords.data());

	if (m_vertInfs.size() > 0)
	{
		m_infbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
		m_infbo->Bind();

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_INT, GL_FALSE, 0, nullptr);

		m_infbo->Update(sizeof(glm::i32vec2) * m_vertInfs.size(), m_vertInfs.data());
	}

	m_fbo->Update(sizeof(glm::i32vec3) * m_faces.size(), m_faces.data());
	glBindVertexArray(0);
}
