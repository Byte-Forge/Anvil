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
	//do this only once? but has to be after the constructor
	m_vbo->Bind();
	m_vbo->Update(sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0]);

	//m_nbo->Bind();
	//m_nbo->Update(sizeof(glm::vec3) * m_normals.size(), &m_normals[0]);

	//m_uvbo->Bind();
	//m_uvbo->Update(sizeof(glm::vec2) * m_uvCoords.size(), &m_uvCoords[0]);

	m_fbo->Bind();
	m_fbo->Update(sizeof(std::uint32_t) * m_faces.size(), &m_faces[0]);
}

void GL::MeshGL::Render(IShader& shader)
{
	glBindVertexArray(m_vao);
	//glUniformMatrix4fv(m_modelMatrixIDs[mode], 1, GL_FALSE, glm::value_ptr(m_mod));
	//glUniformMatrix4fv(m_viewMatrixIDs[mode], 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewMatrix()));
	//glUniformMatrix3fv(m_modelView3x3MatrixIDs[mode], 1, GL_FALSE, glm::value_ptr(glm::mat3(Core::GetCore()->GetCamera()->GetViewMatrix() * m_mod)));
	//glUniformMatrix4fv(m_matrixIDs[mode], 1, GL_FALSE, glm::value_ptr(Core::GetCore()->GetCamera()->GetViewProjectionMatrix() * m_mod));

	//glm::vec3 lightPos = glm::vec3({ m_width / 2.0, 400.0, m_height / 2.0 });
	//glUniform3f(m_lightIDs[mode], lightPos.x, lightPos.y, lightPos.z);

	//glUniform1i(m_tessFactorIDs[mode], Core::GetCore()->GetGraphics()->GetRenderer()->GetTessfactor());
	//glUniform1i(m_maxFactorIDs[mode], Core::GetCore()->GetGraphics()->GetRenderer()->GetMaxTesselation());

	//glActiveTexture(GL_TEXTURE0); //diffuse textures
	//m_diff->Bind();
	//glUniform1i(m_diffIDs[mode], 0);

	//glActiveTexture(GL_TEXTURE1); //normal textures
	//m_nrm->Bind();
	//glUniform1i(m_nrmIDs[mode], 1);

	//glActiveTexture(GL_TEXTURE2); //spec textures
	//m_spec->Bind();
	//glUniform1i(m_specIDs[mode], 2);

	//glActiveTexture(GL_TEXTURE3); //disp textures
	//m_disp->Bind();
	//glUniform1i(m_dispIDs[mode], 3);

	//glActiveTexture(GL_TEXTURE4); //ambi textures
	//m_ambi->Bind();
	//glUniform1i(m_ambiIDs[mode], 4);

	//used for tesselation
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	m_fbo->Bind();
	glDrawElements(GL_PATCHES, (GLsizei)m_faces.size(), GL_UNSIGNED_INT, (void*)0);
}