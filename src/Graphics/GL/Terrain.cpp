//
// Created by stephan on 14.12.15.
//
#include "Terrain.hpp"
#include "flextGL.h"
#include "../../Core.hpp"
#include "../../Math.hpp"
#include "../../Math/Collision.hpp"
#include "../../Math/SimplexNoise.hpp"
#include <iostream>
#include <vector>

//just for testing
#include <ctime>
#include <chrono>

using namespace hpse;

GL::Terrain::Terrain(std::uint32_t width, std::uint32_t height) : m_width(width), m_height(height)
{
	m_quadtree = std::make_shared<Quadtree>(glm::vec2(m_width / 2.f, m_height / 2.f), glm::vec2(m_width / 2.f, m_height / 2.f));

	long long begin = (std::chrono::system_clock::now().time_since_epoch()).count();

	Generate();

	UpdateBufferData();

	long long end = (std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "# created the terrain in: " << (end - begin) / 10000 << "ms" << std::endl;

	//this should be in a WorldBuilder class or sth
	std::vector<std::string> diffuseTextures;
	diffuseTextures.push_back("terrain/gravel_small.dds");
	diffuseTextures.push_back("terrain/grass.dds");
	diffuseTextures.push_back("terrain/rocky_mud.dds");
	diffuseTextures.push_back("terrain/snowy_cliff.dds");

	std::vector<std::string> normTextures;
	normTextures.push_back("terrain/gravel_small_norm.dds");
	normTextures.push_back("terrain/grass_norm.dds");
	normTextures.push_back("terrain/rocky_mud_norm.dds");
	normTextures.push_back("terrain/snowy_cliff_norm.dds");

	std::vector<std::string> specTextures;
	specTextures.push_back("terrain/gravel_small_spec.dds");
	specTextures.push_back("terrain/grass_spec.dds");
	specTextures.push_back("terrain/rocky_mud_spec.dds");
	specTextures.push_back("terrain/snowy_cliff_spec.dds");

	std::vector<std::string> dispTextures;
	dispTextures.push_back("terrain/gravel_small_disp.dds");
	dispTextures.push_back("terrain/grass_disp.dds");
	dispTextures.push_back("terrain/rocky_mud_disp.dds");
	dispTextures.push_back("terrain/snowy_cliff_disp.dds");

	std::vector<std::string> aoTextures;
	aoTextures.push_back("terrain/gravel_small_ao.dds");
	aoTextures.push_back("terrain/grass_ao.dds");
	aoTextures.push_back("terrain/rocky_mud_ao.dds");
	aoTextures.push_back("terrain/snowy_cliff_ao.dds");

	m_diff = Core::GetCore()->GetResources()->GetTextureArray(diffuseTextures);
	m_nrm = Core::GetCore()->GetResources()->GetTextureArray(normTextures);
	m_spec = Core::GetCore()->GetResources()->GetTextureArray(specTextures);
	m_disp = Core::GetCore()->GetResources()->GetTextureArray(dispTextures);
	m_ambi = Core::GetCore()->GetResources()->GetTextureArray(aoTextures);

	for (int i = 0; i < Core::GetCore()->GetGraphics()->GetRenderer()->GetShaderModes().size(); i++)
	{
		m_diffIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("DiffuseTextureSampler", i));
		m_nrmIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("NormalTextureSampler", i));
		m_specIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("SpecularTextureSampler", i));
		m_dispIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("DisplacementTextureSampler", i));
		m_ambiIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("AmbientTextureSampler", i));

		m_modelMatrixIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("M", i));
		m_viewMatrixIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("V", i));
		m_modelView3x3MatrixIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MV3x3", i));
		m_matrixIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("MVP", i));

		m_lightIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("lightPos", i));

		m_tessLevelIDs.push_back(Core::GetCore()->GetGraphics()->GetRenderer()->GetTerrainUniformLocation("maxTessellation", i));
	}

	m_vbo = GL::Buffer(ARRAY_BUFFER);
	m_vbo.Bind();
	m_vbo.Update(m_vertices.size() * sizeof(glm::vec3), &m_vertices[0]);

	m_uvbo = GL::Buffer(ARRAY_BUFFER);
	m_uvbo.Bind();
	m_uvbo.Update(m_uvs.size() * sizeof(glm::vec2), &m_uvs[0]);

	m_nbo = GL::Buffer(ARRAY_BUFFER);
	m_nbo.Bind();
	m_nbo.Update(m_normals.size() * sizeof(glm::vec3), &m_normals[0]);

	m_fbo = GL::Buffer(ELEMENT_ARRAY_BUFFER);
	m_fbo.Bind();
	m_fbo.Update(m_faces.size() * sizeof(std::uint32_t), &m_faces[0]);

	m_mbo = GL::Buffer(ARRAY_BUFFER);
	m_mbo.Bind();
	m_mbo.Update(m_materials.size() * sizeof(std::uint32_t), &m_materials[0]);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
}

GL::Terrain::~Terrain()
{
	glDeleteVertexArrays(1, &m_vao);
	m_vao = 0;
}

int GL::Terrain::GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos)
{
	glm::vec3 origin;
	glm::vec3 direction;
	Core::GetCore()->GetCamera()->ScreenPosToWorldRay(mousePos, origin, direction);
	glm::vec3 point;
	for (unsigned int i = 0; i < m_faces.size(); i += 3)
	{
		if (Collision::Ray_Tri_Intersect(m_vertices[m_faces[i]], m_vertices[m_faces[i + 1]], m_vertices[m_faces[i + 2]], origin, direction, &point))
		{
			pos = point;
			return 1;
		}
	}
	return 0;
}

void GL::Terrain::SetMaterial(glm::vec3 &pos, float radius, int material)
{
	glm::vec2 pos_2 = { pos.x, pos.z };
	for (unsigned int i = pos_2.x - radius + 1; i < pos_2.x + radius + 1; i++)
	{
		for (unsigned int j = pos_2.y - radius + 1; j < pos_2.y + radius + 1; j++)
		{
			glm::vec2 vertex = { i, j };
			if (glm::distance(vertex, pos_2) <= radius)
			{
				m_materialmap[i + j*m_width] = glm::vec3(material, m_materialmap[i + j*m_width].x, m_materialmap[i + j*m_width].z);
				materials_changed = true;
			}
		}
	}
	UpdateBufferData();
}

void GL::Terrain::SetHeight(glm::vec3 &pos, float radius, float height)
{
	glm::vec2 pos_2 = { pos.x, pos.z };
	for (unsigned int i = pos_2.x - radius + 1; i < pos_2.x + radius + 1; i++)
	{
		for (unsigned int j = pos_2.y - radius + 1; j < pos_2.y + radius + 1; j++)
		{
			glm::vec2 vertex = { i, j };
			if (glm::distance(vertex, pos_2) <= radius)
			{
				m_heightmap[i + j*m_width] = height;
				heightmap_changed = true;
			}
		}
	}
	UpdateBufferData();
}

void GL::Terrain::Render(int mode)
{
	glUniformMatrix4fv(m_modelMatrixIDs[mode], 1, GL_FALSE, &m_mod[0][0]);
	glUniformMatrix4fv(m_viewMatrixIDs[mode], 1, GL_FALSE, &Core::GetCore()->GetCamera()->GetViewMatrix()[0][0]);
	glUniformMatrix3fv(m_modelView3x3MatrixIDs[mode], 1, GL_FALSE, &glm::mat3(Core::GetCore()->GetCamera()->GetViewMatrix() * m_mod)[0][0]);
	glUniformMatrix4fv(m_matrixIDs[mode], 1, GL_FALSE, &(Core::GetCore()->GetCamera()->GetViewProjectionMatrix() * m_mod)[0][0]);

	glm::vec3 lightPos = glm::vec3({ m_width/2.0, 400.0, m_height / 2.0 });
	glUniform3f(m_lightIDs[mode], lightPos.x, lightPos.y, lightPos.z);

	glUniform1i(m_tessLevelIDs[mode], Core::GetCore()->GetGraphics()->GetRenderer()->GetTessellationLevel());

	glEnableVertexAttribArray(0);
	m_vbo.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	m_uvbo.Bind();
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	m_nbo.Bind();
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	m_fbo.Bind();

	glEnableVertexAttribArray(3);
	m_mbo.Bind();
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glActiveTexture(GL_TEXTURE0); //diffuse textures
	m_diff->Bind();
	glUniform1i(m_diffIDs[mode], 0);

	glActiveTexture(GL_TEXTURE1); //normal textures
	m_nrm->Bind();
	glUniform1i(m_nrmIDs[mode], 1);

	glActiveTexture(GL_TEXTURE2); //spec textures
	m_spec->Bind();
	glUniform1i(m_specIDs[mode], 2);

	glActiveTexture(GL_TEXTURE3); //disp textures
	m_disp->Bind();
	glUniform1i(m_dispIDs[mode], 3);

	glActiveTexture(GL_TEXTURE4); //ambi textures
	m_ambi->Bind();
	glUniform1i(m_ambiIDs[mode], 4);

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
	if (Core::GetCore()->GetCamera()->GetFrustum()->Updated() || faces_changed)
	{
		m_faces = m_quadtree->GetTriangles(Core::GetCore()->GetCamera()->GetFrustum()->GetFrustumArray());
		if (!m_faces.size() == 0)
		{
			m_fbo.Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faces.size() * sizeof(std::uint32_t), &m_faces[0], GL_STATIC_DRAW);
			faces_changed = false;
		}
	}

	if (heightmap_changed)
	{
		m_vbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

		m_nbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_normals.size(), &m_normals[0], GL_STATIC_DRAW);
		heightmap_changed = false;
	}
	if (uvs_changed)
	{
		m_uvbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_uvs.size(), &m_uvs[0], GL_STATIC_DRAW);
		uvs_changed = false;
	}
	if (materials_changed)
	{
		m_mbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_materials.size(), &m_materials[0], GL_STATIC_DRAW);
		materials_changed = false;
	}
}

void GL::Terrain::Generate()
{
	m_terrainMaterials = Core::GetCore()->GetResources()->GetTerrainMaterials();
	for (int i = 0; i < m_terrainMaterials.size(); i++)
		std::cout << m_terrainMaterials[i] << std::endl;

	for (unsigned int i = 0; i < m_width; i++)
	{
		for (unsigned int j = 0; j < m_height; j++)
		{
			float value = 0.0f;
			
			value += SimplexNoise::scaled_octave_noise_2d(8, 0.7, 0.5, -20.0, 0.0, i / 100.0, j / 100.0); //for slightly evaluation
			float mountain = SimplexNoise::scaled_octave_noise_2d(2, 0.5, 0.1, -10.0, 20.0, i/10.0, j/10.0); //for mountain terrain
			if (value < 0.0)
				value = 0.0;
			if (mountain > 0.0)
				value += SimplexNoise::scaled_octave_noise_2d(8, 0.3, 0.1, 0.0, 10.0, i, j) * mountain / 10.0; //for mountains
			value += SimplexNoise::scaled_octave_noise_2d(5, 0.01, 0.1, 0.0, 2.0, i, j); //for flat terrain

			m_heightmap.push_back(value);

			int mat1 = 0;
			int mat2 = -1;
			float val = 0.5;
			
			if (value > -5)
			{
				mat1 = 0;
				mat2 = 1;
				val = 0.5;
			}
			if (value > 0)
			{
				mat1 = 1;
				mat2 = -1;
				val = 0.0;
			}
			if (value > 3)
			{
				mat1 = 1;
				mat2 = 2;
				val = 0.5;
			}
			if (value > 5)
			{
				mat1 = 2;
				mat2 = -1;
				val = 0.0;
			}
			if (value > 10)
			{
				mat1 = 2;
				mat2 = 3;
				val = 0.2;
			}
			if (value > 15)
			{
				mat1 = 2;
				mat2 = 3;
				val = 0.5;
			}
			if (value > 19)
			{
				mat1 = 3;
				mat2 = -1;
				val = 0.0;
			}

			m_materialmap.push_back({ mat1, mat2, val });
		}
	}
}

void GL::Terrain::ComputeNormals(std::vector<glm::vec3> &normals)
{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	for (unsigned int i = 0; i < m_width; i++)
	{
		for (unsigned int j = 0; j < m_height; j++)
		{
			int index = i + (j * m_width);
			glm::vec3 normal = { 0.0, 0.0, 0.0 };
			a.x = i;
			a.z = j;
			a.y = m_heightmap[index];
			if (i < m_width - 1 && j < m_height - 1)
			{
				b = { i + 1, m_heightmap[index + m_width + 1], j + 1 };
				c = { i + 1, m_heightmap[index + 1], j };
				normal += Math::ComputeNormal(a, b, c);
				b = { i, m_heightmap[index + m_width], j + 1 };
				c = { i + 1, m_heightmap[index + m_width + 1], j + 1};
				normal += Math::ComputeNormal(a, b, c);
			}
			if (j < m_height - 1 && i > 0)
			{
				b = { i - 1, m_heightmap[index - 1], j };
				c = { i, m_heightmap[index + m_width], j + 1 };
				normal += Math::ComputeNormal(a, b, c);
			}
			if (i < m_width - 1 && j > 0)
			{
				b = { i + 1, m_heightmap[index + 1], j };
				c = { i, m_heightmap[index - m_width], j - 1 };
				normal += Math::ComputeNormal(a, b, c);
			}
			if (i > 0 && j > 0)
			{
				b = { i, m_heightmap[index - m_width], j - 1};
				c = { i - 1, m_heightmap[index - m_width - 1], j - 1 };
				normal += Math::ComputeNormal(a, b, c);
				b = { i - 1, m_heightmap[index - m_width - 1], j - 1 };
				c = { i - 1, m_heightmap[index - 1], j };
				normal += Math::ComputeNormal(a, b, c);
			}
			normals.push_back(glm::normalize(normal));
		}
	}
}

void GL::Terrain::UpdateBufferData()
{
	std::vector<glm::vec3> normals;
	if (heightmap_changed)
	{
		ComputeNormals(normals);

		m_vertices.clear();
		m_normals.clear();
	}
	if (uvs_changed)
		m_uvs.clear();
	if (materials_changed)
		m_materials.clear();

	//fill the vectors for buffer objects
	int index = 0;
	for (unsigned int i = 0; i < m_width - 1; i++)
	{
		for (unsigned int j = 0; j < m_height - 1; j++)
		{
			glm::vec3 a = { (float)i, m_heightmap[i + j * m_width], (float)j };
			glm::vec3 b = { (float)(i + 1), m_heightmap[i + 1 + j * m_width], (float)j };
			glm::vec3 c = { (float)(i + 1), m_heightmap[i + 1 + (j + 1) * m_width], (float)(j + 1) };
			glm::vec3 d = { (float)i, m_heightmap[i + (j + 1) * m_width], (float)(j + 1) };

			if (heightmap_changed)
			{
				m_vertices.push_back(a);
				m_vertices.push_back(b);
				m_vertices.push_back(c);

				m_vertices.push_back(a);
				m_vertices.push_back(c);
				m_vertices.push_back(d);

				m_normals.push_back(normals[j + i * m_width]);
				m_normals.push_back(normals[j + 1 + i * m_width]);
				m_normals.push_back(normals[j + 1 + (i + 1) * m_width]);

				m_normals.push_back(normals[j + i * m_width]);
				m_normals.push_back(normals[j + 1 + (i + 1)*m_width]);
				m_normals.push_back(normals[j + (i + 1)*m_width]);
			}
		
			if (uvs_changed)
			{
				int val = 4;
				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });

				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });
				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });
			}

			if (materials_changed)
			{
				m_materials.push_back(m_materialmap[i + j*m_width]);
				m_materials.push_back(m_materialmap[i + 1 + j*m_width]);
				m_materials.push_back(m_materialmap[i + 1 + (j + 1)*m_width]);

				m_materials.push_back(m_materialmap[i + j*m_width]);
				m_materials.push_back(m_materialmap[i + 1 + (j + 1)*m_width]);
				m_materials.push_back(m_materialmap[i + (j + 1)*m_width]);
			}

			if (faces_changed)
			{
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
	}
}