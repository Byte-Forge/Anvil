/*
************************************
* Copyright (C) 2016 ByteForge
* Terrain.cpp
************************************
*/

#include "TerrainGL.hpp"
#include "flextGL.h"
#include "../../Core.hpp"
#include "../../Math.hpp"
#include "../../Math/SimplexNoise.hpp"
#include "../Camera.hpp"
#include "../IRenderer.hpp"
#include "../../Graphics.hpp"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

using namespace anvil;

GL::Terrain::Terrain(std::uint32_t width, std::uint32_t height) : ITerrain(width,height), m_vao(0)
{
	UpdateBufferData();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_vbo->Update(static_cast<unsigned int>(m_vertices.size() * sizeof(glm::vec3)), m_vertices.data());

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_uvbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_uvbo->Update(static_cast<unsigned int>(m_uvs.size() * sizeof(glm::vec2)), m_uvs.data());
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_nbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_nbo->Update(static_cast<unsigned int>(m_normals.size() * sizeof(glm::vec3)), m_normals.data());

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_mbo = std::make_unique<GL::Buffer>(ARRAY_BUFFER);
	m_mbo->Update(static_cast<unsigned int>(m_materials.size() * sizeof(std::uint32_t)), m_materials.data());

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	m_fbo = std::make_unique<GL::Buffer>(ELEMENT_ARRAY_BUFFER);
	m_fbo->Update(static_cast<unsigned int>(m_faces.size() * sizeof(std::uint32_t)), m_faces.data());
}

GL::Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &m_vao);
	m_vao = 0;
}

int GL::Terrain::Render(IShader& shader)
{
	glBindVertexArray(m_vao);

	glActiveTexture(GL_TEXTURE0); //diffuse textures
	m_diff->Bind();
	glUniform1i(shader.GetUniform("albedoTex"), 0);

	glActiveTexture(GL_TEXTURE1); //normal textures
	m_nrm->Bind();
	glUniform1i(shader.GetUniform("normalTex"), 1);

	glActiveTexture(GL_TEXTURE2); //spec textures
	m_spec->Bind();
	glUniform1i(shader.GetUniform("specularTex"), 2);

	glActiveTexture(GL_TEXTURE3); //disp textures
	m_disp->Bind();
	glUniform1i(shader.GetUniform("displacementTex"), 3);

	glActiveTexture(GL_TEXTURE4); //ambi textures
	m_ambi->Bind();
	glUniform1i(shader.GetUniform("ambientTex"), 4);

	//used for tesselation
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	m_fbo->Bind();
	glDrawElements(GL_PATCHES, (GLsizei)m_faces.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);

	return m_faces.size()/3;
}

void GL::Terrain::Update()
{
	if (Core::GetCore()->GetCamera()->GetFrustum()->Updated() || faces_changed)
	{
		m_faces = m_quadtree->GetTriangles(Core::GetCore()->GetCamera()->GetFrustum()->GetFrustumArray());
		if (m_faces.size() > 0)
		{
			m_fbo->Update(m_faces.size() * sizeof(std::uint32_t), &m_faces[0]);
			faces_changed = false;
		}
	}

	if (heightmap_changed)
	{
		m_vbo->Update(sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0]);

		m_nbo->Update(sizeof(glm::vec3) * m_normals.size(), &m_normals[0]);
		heightmap_changed = false;
	}
	if (uvs_changed)
	{
		m_uvbo->Update(sizeof(glm::vec2) * m_uvs.size(), &m_uvs[0]);
		uvs_changed = false;
	}
	if (materials_changed)
	{
		m_mbo->Update(sizeof(glm::vec3) * m_materials.size(), &m_materials[0]);
		materials_changed = false;
	}
}