//
// Created by stephan on 14.12.15.
//

#include "Terrain.hpp"
#include "flextGL.h"
#include "../../Core.hpp"
#include <iostream>

using namespace hpse;

GL::Terrain::Terrain(std::uint32_t width, std::uint32_t height)
{
	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			m_vertices.push_back({ (float)i * 10.0, glm::sin(i + j)* (j % 3) + glm::cos(j) * (i % 4), (float)j * 10.0});

			m_uvs.push_back({ i % 10 / 10.0f, j % 10 / 10.0f });

			m_normals.push_back({ 0.0, 1.0, 0.0 });

			m_tangents.push_back({0.0, 0.0, 1.0});

			m_bitangents.push_back({ 1.0, 0.0, 0.0 });
		}
	}

	//create the indices needed to render the triangles
	for (std::uint32_t i = 0; i < height - 1; i++)
	{
		for (std::uint32_t j = 0; j < width - 1; j++)
		{
			m_faces.push_back(i + (j*width));
			m_faces.push_back(i + (j*width) + width);
			m_faces.push_back(i + (j*width) + width + 1);

			m_faces.push_back(i + (j*width));
			m_faces.push_back(i + (j*width) + width + 1);
			m_faces.push_back(i + (j*width) + 1);
		}
	}

	m_ambient = glm::vec3({ 0.6f, 0.6f, 0.6f });
	m_diffuse = glm::vec3({0.8f, 0.8f, 0.8f});
	m_lightDir = glm::vec3({ -0.1f, -1.0f, -0.1f });

	m_diff = Core::GetResources()->GetResource("pepples_01", ResourceType::texture);
	m_nrm = Core::GetResources()->GetResource("pepples_01_nrm", ResourceType::texture);
	m_spec = Core::GetResources()->GetResource("pepples_01_spec", ResourceType::texture);

	m_matrixID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MVP");	
	m_viewMatrixID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("V");
	m_modelMatrixID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("M");
	m_modelView3x3MatrixID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MV3x3");

	m_diffID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("DiffuseTextureSampler");
	m_nrmID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("NormalTextureSampler");
	m_specID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("SpecularTextureSampler");

	m_lightID = Core::GetGraphics()->GetRenderer()->GetTerrainUniformLocation("LightPosition_worldspace");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
	glBufferData(GL_ARRAY_BUFFER, m_uvs.size() * sizeof(glm::vec2), &m_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_nbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(glm::vec3), &m_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_tbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
	glBufferData(GL_ARRAY_BUFFER, m_tangents.size() * sizeof(glm::vec3), &m_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_btbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_btbo);
	glBufferData(GL_ARRAY_BUFFER, m_bitangents.size() * sizeof(glm::vec3), &m_bitangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_fbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(std::uint32_t), &m_faces[0], GL_STATIC_DRAW);
}

GL::Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &m_vao);
	m_vao = 0;

	glDeleteBuffers(1, &m_vbo);
	m_vbo = 0;

	glDeleteBuffers(1, &m_uvbo);
	m_uvbo = 0;

	glDeleteBuffers(1, &m_nbo);
	m_nbo = 0;

	glDeleteBuffers(1, &m_tbo);
	m_tbo = 0;

	glDeleteBuffers(1, &m_btbo);
	m_btbo = 0;

	glDeleteBuffers(1, &m_fbo);
	m_fbo = 0;
}

void GL::Terrain::Render()
{ 
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &(Core::GetCamera()->GetViewProjectionMatrix() * m_mod)[0][0]);
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_mod[0][0]);
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &Core::GetCamera()->GetViewMatrix()[0][0]);
	glUniformMatrix3fv(m_modelView3x3MatrixID, 1, GL_FALSE, &glm::mat3(Core::GetCamera()->GetViewMatrix() * m_mod)[0][0]);

	glm::vec3 lightPos = Core::GetCamera()->GetLookAt() + glm::vec3({0.0, 100.0, 0.0});
	glUniform3f(m_lightID, lightPos.x, lightPos.y, lightPos.z);

	glActiveTexture(GL_TEXTURE0); //diffuse texture
	std::dynamic_pointer_cast<ITexture> (m_diff)->Bind();
	glUniform1i(m_diffID, 0);

	glActiveTexture(GL_TEXTURE1); //normal texture
	std::dynamic_pointer_cast<ITexture> (m_nrm)->Bind();
	glUniform1i(m_nrmID, 1);

	glActiveTexture(GL_TEXTURE2); //spec texture
	std::dynamic_pointer_cast<ITexture> (m_spec)->Bind();
	glUniform1i(m_specID, 2);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, m_tbo);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, m_btbo);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fbo);


	glDrawElements(GL_TRIANGLES, (GLsizei)m_faces.size(), GL_UNSIGNED_INT, (void*)0);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void GL::Terrain::Update()
{	

	m_mod = glm::mat4(1.0);
	if (updated)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_uvs.size(), &m_uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normals.size(), &m_normals[0], GL_STATIC_DRAW);

		updated = false;
	}
}
