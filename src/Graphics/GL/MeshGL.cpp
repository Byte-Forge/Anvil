/*
************************************
* Copyright (C) 2016 ByteForge
* MeshGL.cpp
************************************
*/

#include "MeshGL.hpp"
#include <iostream>

using namespace anvil;

GL::MeshGL::MeshGL()
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_vbo->Bind();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_uvbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_uvbo->Bind();
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_nbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_nbo->Bind();

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_fbo = std::make_unique<GL::Buffer>(ELEMENT_ARRAY_BUFFER);
	m_fbo->Bind();
}

GL::MeshGL::~MeshGL()
{
	glDeleteVertexArrays(1, &m_vao);
	m_vao = 0;
}

void GL::MeshGL::Update()
{
	m_vbo->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	m_nbo->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normals.size(), &m_normals[0], GL_STATIC_DRAW);

	m_uvbo->Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_uvCoords.size(), &m_uvCoords[0], GL_STATIC_DRAW);

	m_fbo->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(std::uint32_t), &m_faces[0], GL_STATIC_DRAW);
}