//
// Created by stephan on 14.12.15.
//

#include "Terrain.hpp"
#include "flextGL.h"
#include "../../Core.hpp"
#include "../../Math.hpp"
#include <iostream>
#include <vector>

//just for testing
#include <ctime>
#include <chrono>

using namespace hpse;

GL::Terrain::Terrain(std::uint32_t width, std::uint32_t height) : m_width(width), m_height(height)
{
	m_quadtree = std::make_shared<Quadtree>(glm::vec2(width / 2.f, height / 2.f), glm::vec2(width / 2.f, height / 2.f));

	long long begin = (std::chrono::system_clock::now().time_since_epoch()).count();

	//generate a heightmap
	
	std::vector<float> heightmap;
	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			heightmap.push_back((glm::sin(i + j)* (j % 3) + glm::cos(j) * (i % 4)) / 10.0);
		}
	}

	//compute the normals
	std::vector<glm::vec3> normals;
	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			int index = i + (j*width);
			glm::vec3 normal = {0.0, 0.0, 0.0};
			if (i < width - 1 && j < height - 1)
			{
				normal += Math::ComputeNormal(heightmap[index], heightmap[index + j + 1], heightmap[index + 1]);
				normal += Math::ComputeNormal(heightmap[index], heightmap[index + j], heightmap[index + j + 1]);
			}
			if (j < height - 1 && i > 0)
			{
				normal += Math::ComputeNormal(heightmap[index], heightmap[index - 1], heightmap[index + j]);
			}
			if (i < width - 1 && j > 0)
			{
				normal += Math::ComputeNormal(heightmap[index], heightmap[index + 1], heightmap[index - j]);
			}
			if (i > 0 && j > 0)
			{
				normal += Math::ComputeNormal(heightmap[index], heightmap[index - j], heightmap[index - j - 1]);
				normal += Math::ComputeNormal(heightmap[index], heightmap[index - j - 1], heightmap[index - 1]);
			}
			normals.push_back(glm::normalize(normal));
		}
	}

	//generate material indices
	std::vector<glm::vec3> materials;
	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			int r = i % 4;
			int mat1, mat2;
			float val;
			if (r == 0)
			{
				mat1 = 0;
				mat2 = -1;
				val = 0;
			}
			else if (r == 1)
			{
				mat1 = 0;
				mat2 = 1;
				val = 0.5;
			}
			else if (r == 2)
			{
				mat1 = 1;
				mat2 = -1;
				val = 0;
			}
			else if (r == 3)
			{
				mat1 = 1;
				mat2 = 0;
				val = 0.5;
			}
			materials.push_back({mat1, mat2, val});
		}
	}

	//fill the vectors for buffer objects
	int index = 0;
	for (std::uint32_t i = 0; i < width - 1; i++)
	{
		for (std::uint32_t j = 0; j < height - 1; j++)
		{
			glm::vec3 a = { (float)i, heightmap[i + j*width], (float)j };
			glm::vec3 b = { (float)(i+1), heightmap[i + 1 + j*width], (float)j };
			glm::vec3 c = { (float)(i + 1), heightmap[i + 1 + (j+1)*width], (float)(j + 1) };
			glm::vec3 d = { (float)i, heightmap[i + (j+1)*width], (float)(j+1) };

			m_vertices.push_back(a);
			m_vertices.push_back(b);
			m_vertices.push_back(c);

			m_vertices.push_back(a);
			m_vertices.push_back(c);
			m_vertices.push_back(d);

			m_uvs.push_back({ 0.0, 0.0 });
			m_uvs.push_back({ 1.0, 0.0 });
			m_uvs.push_back({ 1.0, 1.0 });

			m_uvs.push_back({ 0.0, 0.0 });
			m_uvs.push_back({ 1.0, 1.0 });
			m_uvs.push_back({ 0.0, 1.0 });

			m_normals.push_back(normals[i + j*width]);
			m_normals.push_back(normals[i + 1 + j*width]);
			m_normals.push_back(normals[i + 1 + (j + 1)*width]);

			m_normals.push_back(normals[i + j*width]);
			m_normals.push_back(normals[i + 1 + (j + 1)*width]);
			m_normals.push_back(normals[i + (j + 1)*width]);

			m_materials.push_back(materials[i + j*width]);
			m_materials.push_back(materials[i + 1 + j*width]);
			m_materials.push_back(materials[i + 1 + (j + 1)*width]);

			m_materials.push_back(materials[i + j*width]);
			m_materials.push_back(materials[i + 1 + (j + 1)*width]);
			m_materials.push_back(materials[i + (j + 1)*width]);

			m_faces.push_back(index++);
			m_faces.push_back(index++);
			m_faces.push_back(index++);

			m_quadtree->AddTriangle(&m_faces[index - 3], a, b, c);

			m_faces.push_back(index++);
			m_faces.push_back(index++);
			m_faces.push_back(index++);

			m_quadtree->AddTriangle(&m_faces[index - 3], a, c, d);
		}
	}

	long long end = (std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "# created the terrain in: " << (end - begin) / 10000 << "ms" << std::endl;

	std::vector<std::string> diffuseTextures;
	diffuseTextures.push_back("terrain/cobble_fan.dds");
	diffuseTextures.push_back("terrain/grass.dds");

	std::vector<std::string> normTextures;
	normTextures.push_back("terrain/cobble_fan_norm.dds");
	normTextures.push_back("terrain/grass_norm.dds");

	std::vector<std::string> specTextures;
	specTextures.push_back("terrain/cobble_fan_spec.dds");
	specTextures.push_back("terrain/grass_spec.dds");

	std::vector<std::string> dispTextures;
	dispTextures.push_back("terrain/cobble_fan_disp.dds");
	dispTextures.push_back("terrain/grass_disp.dds");

	std::vector<std::string> aoTextures;
	aoTextures.push_back("terrain/cobble_fan_ao.dds");
	aoTextures.push_back("terrain/grass_ao.dds");

	m_diff = Core::GetCore()->GetResources()->GetTextureArray(diffuseTextures);
	m_nrm = Core::GetCore()->GetResources()->GetTextureArray(normTextures);
	m_spec = Core::GetCore()->GetResources()->GetTextureArray(specTextures);
	m_disp = Core::GetCore()->GetResources()->GetTextureArray(dispTextures);
	m_ambi = Core::GetCore()->GetResources()->GetTextureArray(aoTextures);

	m_diffID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("DiffuseTextureSampler");
	m_nrmID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("NormalTextureSampler");
	m_specID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("SpecularTextureSampler");
	m_dispID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("DisplacementTextureSampler");
	m_ambiID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("AmbientTextureSampler");

	m_modelMatrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("M");
	m_viewMatrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("V");
	m_modelView3x3MatrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MV3x3");
	m_matrixID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MVP");

	m_lightID = Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("lightPos");

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

	glGenBuffers(1, &m_fbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(std::uint32_t), &m_faces[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_mbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_materials.size() * sizeof(std::uint32_t), &m_materials[0], GL_STATIC_DRAW);
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

	glDeleteBuffers(1, &m_fbo);
	m_fbo = 0;

	glDeleteBuffers(1, &m_mbo);
	m_mbo = 0;
}

void GL::Terrain::Render()
{
	glUniformMatrix4fv(m_modelMatrixID, 1, GL_FALSE, &m_mod[0][0]);
	glUniformMatrix4fv(m_viewMatrixID, 1, GL_FALSE, &Core::GetCore()->GetCamera()->GetViewMatrix()[0][0]);
	glUniformMatrix3fv(m_modelView3x3MatrixID, 1, GL_FALSE, &glm::mat3(Core::GetCore()->GetCamera()->GetViewMatrix() * m_mod)[0][0]);
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &(Core::GetCore()->GetCamera()->GetViewProjectionMatrix() * m_mod)[0][0]);

	glm::vec3 lightPos = glm::vec3({ 20.0, 20.0, 20.0 });
	glUniform3f(m_lightID, lightPos.x, lightPos.y, lightPos.z);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fbo);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, m_mbo);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glActiveTexture(GL_TEXTURE0); //diffuse textures
	m_diff->Bind();
	glUniform1i(m_diffID, 0);

	glActiveTexture(GL_TEXTURE1); //normal textures
	m_nrm->Bind();
	glUniform1i(m_nrmID, 1);

	glActiveTexture(GL_TEXTURE2); //spec textures
	m_spec->Bind();
	glUniform1i(m_specID, 2);

	glActiveTexture(GL_TEXTURE3); //disp textures
	m_disp->Bind();
	glUniform1i(m_dispID, 3);

	glActiveTexture(GL_TEXTURE4); //ambi textures
	m_ambi->Bind();
	glUniform1i(m_ambiID, 4);

	//used for tesselation
	glPatchParameteri(GL_PATCH_VERTICES, 3);

	glDrawElements(GL_PATCHES, (GLsizei)m_faces.size(), GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void GL::Terrain::Update()
{
	m_mod = glm::mat4(1.0);

	if (Core::GetCore()->GetCamera()->GetFrustum()->Updated())
	{
		m_faces = m_quadtree->GetTriangles(Core::GetCore()->GetCamera()->GetFrustum()->GetFrustumArray());
		if (m_faces.size() != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_fbo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(std::uint32_t), &m_faces[0], GL_STATIC_DRAW);
		}
	}

	if (updated)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_uvbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_uvs.size(), &m_uvs[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normals.size(), &m_normals[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_mbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_materials.size(), &m_materials[0], GL_STATIC_DRAW);

		updated = false;
	}
}