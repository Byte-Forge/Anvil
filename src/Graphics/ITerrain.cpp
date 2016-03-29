/*
************************************
* Copyright (C) 2016 ByteForge
* ITerrain.cpp
************************************
*/

#include "ITerrain.hpp"
#include "../Core.hpp"
#include "../Math/SimplexNoise.hpp"
#include "../Math/Collision.hpp"
#include "../Math.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/intersect.hpp"
#include "Camera.hpp"
#include "../Core/ResourceHandler.hpp"
#include "Material.hpp"
#include "../Objects/Entity.hpp"

#include <future>

using namespace anvil;

ITerrain::ITerrain(std::uint32_t width, std::uint32_t height) : m_width(width), m_height(height)
{
}

int ITerrain::GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos)
{
	glm::vec3 origin;
	glm::vec3 direction;
	Core::GetCore()->GetCamera()->ScreenPosToWorldRay(mousePos, origin, direction);
	glm::vec3 point;
	for (unsigned int i = 0; i < m_faces.size(); i += 3)
	{
		if (glm::intersectRayTriangle(origin, direction, m_vertices[m_faces[i]], m_vertices[m_faces[i + 1]], m_vertices[m_faces[i + 2]], point))
		{
			pos = point;
			return 1;
		}
	}
	return 0;
}

void ITerrain::SetMaterial(glm::vec3 &pos, float radius, int material)
{
	glm::vec2 pos_2 = { pos.x, pos.z };
	for (unsigned int i = pos_2.x - radius + 1; i < pos_2.x + radius + 1; i++)
	{
		for (unsigned int j = pos_2.y - radius + 1; j < pos_2.y + radius + 1; j++)
		{
			glm::vec2 vertex = { i, j };
			if (glm::distance(vertex, pos_2) <= radius)
			{
				m_materialmap[i][j] = glm::vec3(material, m_materialmap[i][j].x, m_materialmap[i][j].z);
				materials_changed = true;
			}
		}
	}
	UpdateBufferData();
}

void ITerrain::SetHeight(glm::vec3 &pos, float radius, float height)
{
	glm::vec2 pos_2 = { pos.x, pos.z };
	for (unsigned int i = pos_2.x - radius + 1; i < pos_2.x + radius + 1; i++)
	{
		for (unsigned int j = pos_2.y - radius + 1; j < pos_2.y + radius + 1; j++)
		{
			glm::vec2 vertex = { i, j };
			if (glm::distance(vertex, pos_2) <= radius)
			{
				m_heightmap[i][j] = height;
				heightmap_changed = true;
			}
		}
	}
	UpdateBufferData();
}

void ITerrain::Generate()
{
	//m_terrainMaterials = Core::GetCore()->GetResources()->GetTerrainMaterials();
	m_terrainMaterials.push_back("terrain/grass.json");
	m_terrainMaterials.push_back("terrain/grass_2.json");
	m_terrainMaterials.push_back("terrain/grass_3.json");
	m_terrainMaterials.push_back("terrain/grass_4.json");
	m_terrainMaterials.push_back("terrain/cliff_snowy.json");

	auto hand = std::async(std::launch::async, &ITerrain::CreateHeightmap, this);
	UpdateTextures();
	//wait until heightmap creation is done
	hand.get();
}

void ITerrain::ComputeNormals(std::vector<std::vector<glm::vec3>> &normals)
{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	for (unsigned int i = 0; i <= m_width; i++)
	{
		std::vector<glm::vec3> n;
		normals.push_back(n);
		for (unsigned int j = 0; j <= m_height; j++)
		{
			glm::vec3 normal = { 0.0, 0.0, 0.0 };
			a.x = i;
			a.z = j;
			a.y = m_heightmap[i][j];
			if (i < m_width - 1 && j < m_height - 1)
			{
				b = { i + 1, m_heightmap[i+1][j+1], j + 1 };
				c = { i + 1, m_heightmap[i+1][j], j };
				normal += Math::ComputeNormal(a, b, c);
				b = { i, m_heightmap[i][j+1], j + 1 };
				c = { i + 1, m_heightmap[i+1][j+1], j + 1 };
				normal += Math::ComputeNormal(a, b, c);
			}
			if (i > 0 && j > 0)
			{
				b = { i, m_heightmap[i][j-1], j - 1 };
				c = { i - 1, m_heightmap[i-1][j-1], j - 1 };
				normal += Math::ComputeNormal(a, b, c);
				b = { i - 1, m_heightmap[i-1][j-1], j - 1 };
				c = { i - 1, m_heightmap[i - 1][j], j };
				normal += Math::ComputeNormal(a, b, c);
			}
			normals[i].push_back(glm::normalize(normal));
		}
	}
}

void ITerrain::CreateHeightmap()
{
	std::shared_ptr<Entity> tree = Core::GetCore()->GetResources()->GetEntity("terrain/tree.json");

	for (unsigned int i = 0; i <= m_width; i++)
	{
		std::vector<float> v;
		m_heightmap.push_back(v);

		std::vector<glm::vec3> m;
		m_materialmap.push_back(m);
		for (unsigned int j = 0; j <= m_height; j++)
		{
			float value = 0.0f;
			value += SimplexNoise::scaled_octave_noise_2d(8, 0.7f, 0.5f, -20.0f, 0.0f, i / 100.0f, j / 100.0f); //for slightly evaluation
			float mountain = SimplexNoise::scaled_octave_noise_2d(2, 0.5f, 0.1f, -10.0f, 20.0f, i / 10.0f, j / 10.0f); //for mountain terrain
			if (value < 0.0)
				value = 0.0;
			if (mountain > 0.0)
				value += SimplexNoise::scaled_octave_noise_2d(8, 0.3f, 0.1f, 0.0f, 10.0f, i, j) * mountain / 10.0; //for mountains

			value += SimplexNoise::scaled_octave_noise_2d(5, 0.01f, 0.1f, 0.0f, 2.0f, i, j); //for flat terrain

			m_heightmap[i].push_back(value);

			//tree->AddInstance(glm::vec3(i, value, j));

			int mat1 = 0;
			int mat2 = -1;
			float val = 0.0f;

			if (value > -5)
				mat1 = 1;
			if (value > 0)
				mat1 = 2;
			if (value > 5)
				mat1 = 3;
			if (value > 10)
				mat1 = 4;

			m_materialmap[i].push_back({ mat1, mat2, val });
		}
	}
}

void ITerrain::UpdateBufferData()
{
	std::vector<std::vector<glm::vec3>> normals;
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
	for (unsigned int i = 0; i < m_width; i++)
	{
		for (unsigned int j = 0; j < m_height; j++)
		{
			glm::vec3 a = { (float)i, m_heightmap[i][j], (float)j };
			glm::vec3 b = { (float)(i + 1), m_heightmap[i + 1][j], (float)j };
			glm::vec3 c = { (float)(i + 1), m_heightmap[i + 1][j + 1], (float)(j + 1) };
			glm::vec3 d = { (float)i, m_heightmap[i][j + 1], (float)(j + 1) };

			if (heightmap_changed)
			{
				m_vertices.push_back(a);				
				m_vertices.push_back(c);
				m_vertices.push_back(b);

				m_vertices.push_back(a);			
				m_vertices.push_back(d);
				m_vertices.push_back(c);

				m_normals.push_back(normals[i][j]);			
				m_normals.push_back(normals[i + 1][j + 1]);
				m_normals.push_back(normals[i + 1][j]);

				m_normals.push_back(normals[i][j]);			
				m_normals.push_back(normals[i][j + 1]);
				m_normals.push_back(normals[i + 1][j + 1]);
			}

			if (uvs_changed)
			{
				int val = 4;
				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });			
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });

				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 0.0 + j % val * 1.0 / val });			
				m_uvs.push_back({ 0.0 + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });
				m_uvs.push_back({ 1.0 / val + i % val * 1.0 / val, 1.0 / val + j % val * 1.0 / val });
			}

			if (materials_changed)
			{
				m_materials.push_back(m_materialmap[i][j+1]);			
				m_materials.push_back(m_materialmap[i+1][j+1]);
				m_materials.push_back(m_materialmap[i + 1][j + 1]);

				m_materials.push_back(m_materialmap[i][j+1]);				
				m_materials.push_back(m_materialmap[i][j+1]);
				m_materials.push_back(m_materialmap[i + 1][j + 1]);
			}

			if (faces_changed)
			{
				m_faces.push_back(index++);
				m_faces.push_back(index++);
				m_faces.push_back(index++);

				m_quadtree->AddTriangle(&m_faces[index - 3], c, b, a);

				m_faces.push_back(index++);
				m_faces.push_back(index++);
				m_faces.push_back(index++);

				m_quadtree->AddTriangle(&m_faces[index - 3], d, c, a);
			}
		}
	}
}

void ITerrain::UpdateTextures()
{
	std::vector<std::string> diffuseTextures;
	std::vector<std::string> normTextures;
	std::vector<std::string> specTextures;
	std::vector<std::string> dispTextures;
	std::vector<std::string> aoTextures;

	for (auto& mat: m_terrainMaterials)
	{
		std::shared_ptr<Material> m = Core::GetCore()->GetResources()->GetMaterial(mat);
		diffuseTextures.push_back(m->GetDiffuseTexture());
		normTextures.push_back(m->GetNormalTexture());
		specTextures.push_back(m->GetSpecularTexture());
		dispTextures.push_back(m->GetDisplacementTexture());
		aoTextures.push_back(m->GetAmbientOcclusionTexture());
	}

	m_diff = Core::GetCore()->GetResources()->GetTextureArray(diffuseTextures);
	m_nrm = Core::GetCore()->GetResources()->GetTextureArray(normTextures);
	m_spec = Core::GetCore()->GetResources()->GetTextureArray(specTextures);
	m_disp = Core::GetCore()->GetResources()->GetTextureArray(dispTextures);
	m_ambi = Core::GetCore()->GetResources()->GetTextureArray(aoTextures);
}