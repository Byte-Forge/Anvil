/*
************************************
* Copyright (C) 2016 ByteForge
* ITerrain.cpp
************************************
*/

#include "ITerrain.hpp"
#include "ITexture.hpp"
#include "Quadtree.hpp"
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

#include <chrono>
#include <future>

using namespace anvil;

ITerrain::ITerrain(std::uint32_t width, std::uint32_t height) : m_width(width), m_height(height)
{
	srand(time(NULL));
	m_quadtree = std::make_shared<Quadtree>(glm::vec2(m_width / 2.f, m_height / 2.f), glm::vec2(m_width / 2.f, m_height / 2.f));
	Generate();
}

//implemented with binary search
int ITerrain::GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos)
{
	float epsilon = 0.1f;
	glm::vec3 origin;
	glm::vec3 direction;
	Core::GetCore()->GetCamera()->ScreenPosToWorldRay(mousePos, origin, direction);
	float distance = 500;

	glm::vec3 testPoint = origin + direction * distance;
	int count = 0;
	while (count < 100)
	{
		float height = GetHeight(testPoint.x, testPoint.z);
		float difference = glm::abs(testPoint.y - height);
		if (difference < epsilon)
		{
			pos = testPoint;
			return 1;
		}
		else if (testPoint.y > height)
		{
			testPoint += direction*distance;
		}
		else if (testPoint.y < height)
		{
			distance /= 2.0f;
			testPoint -= direction*distance;
		}
		count++;
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
			if (i < 0 || j < 0 || i > m_width || j > m_height)
				continue;
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
			if (i < 0 || j < 0 || i > m_width || j > m_height)
				continue;
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
	auto begin = std::chrono::system_clock::now();

	//m_terrainMaterials = Core::GetCore()->GetResources()->GetTerrainMaterials();
	m_terrainMaterials.push_back("materials/terrain/medieval_pavement.json");
	m_terrainMaterials.push_back("materials/terrain/dirt.json");

	auto hand = std::async(std::launch::async, &ITerrain::CreateHeightmap, this);
	UpdateTextures();

	std::shared_ptr<Entity> oak = Core::GetCore()->GetResources()->GetEntity("entities/terrain/misc/oak.json");
	std::shared_ptr<Entity> douglas_fir = Core::GetCore()->GetResources()->GetEntity("entities/terrain/misc/douglas_fir.json"); 
	//std::shared_ptr<Entity> hemlock_fir = Core::GetCore()->GetResources()->GetEntity("entities/terrain/misc/hemlock_fir.json");
	//std::shared_ptr<Entity> rhododendron = Core::GetCore()->GetResources()->GetEntity("entities/terrain/misc/rhododendron.json");


	auto ent1 = glm::vec3(10, 0.5, 10);
	//oak->AddInstance(ent1, glm::vec3(0.0, -45.0f, 0.0));

	//wait until heightmap creation is done
	hand.get();


	/////////////////////////////////////////////////////// MOD STUFF ////////////////////////////////////////////////////////////////

	std::shared_ptr<Entity> castle = Core::GetCore()->GetResources()->GetEntity("entities/structures/gondor/castle.json");

	std::shared_ptr<Entity> uruk_cross = Core::GetCore()->GetResources()->GetEntity("entities/units/isengard/urukhai_crossbow.json");

	auto ent = glm::vec3(50, 0.5, 50);
	//castle->AddInstance(ent, glm::vec3(0.0, -45.0f, 0.0));


	ent = glm::vec3(20, m_heightmap[50][50], 20);
	//uruk_cross->AddInstance(ent);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "# created the terrain in: " << duration.count() << "ms" << std::endl;
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
	for (unsigned int i = 0; i <= m_width; i++)
	{
		std::vector<float> v;
		m_heightmap.push_back(v);

		std::vector<glm::vec3> m;
		m_materialmap.push_back(m);
		for (unsigned int j = 0; j <= m_height; j++)
		{
			float value = 0.0f;
			/*
			value += SimplexNoise::scaled_octave_noise_2d(8, 0.7f, 0.5f, -20.0f, 0.0f, i / 100.0f, j / 100.0f); //for slightly evaluation
			float mountain = SimplexNoise::scaled_octave_noise_2d(2, 0.5f, 0.1f, -10.0f, 20.0f, i / 10.0f, j / 10.0f); //for mountain terrain
			if (value < 0.0)
				value = 0.0;
			if (mountain > 0.0)
				value += SimplexNoise::scaled_octave_noise_2d(8, 0.3f, 0.1f, 0.0f, 10.0f, i, j) * mountain / 10.0; //for mountains

			value += SimplexNoise::scaled_octave_noise_2d(5, 0.01f, 0.1f, 0.0f, 2.0f, i, j); //for flat terrain
			*/
			m_heightmap[i].push_back(value);

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
		//also clear faces and recreate the quadtree
		//or update faces?

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
				int val = 16; //over how many quads the texture is stretched
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
		diffuseTextures.push_back(m->GetAlbedoTextureString());
		normTextures.push_back(m->GetNormalTextureString());
		specTextures.push_back(m->GetSpecularTextureString());
		dispTextures.push_back(m->GetDisplacementTextureString());
		aoTextures.push_back(m->GetAmbientOcclusionTextureString());
	}

	m_diff = Core::GetCore()->GetResources()->GetTextureArray(diffuseTextures);
	m_nrm = Core::GetCore()->GetResources()->GetTextureArray(normTextures);
	m_spec = Core::GetCore()->GetResources()->GetTextureArray(specTextures);
	m_disp = Core::GetCore()->GetResources()->GetTextureArray(dispTextures);
	m_ambi = Core::GetCore()->GetResources()->GetTextureArray(aoTextures);
}

float ITerrain::GetHeight(float x, float y)
{
	if (x < 0.0 || y < 0.0 || x > m_width || y > m_height)
		return 0.0f;
	int ix = x;
	int iy = y;
	float xoffset = x - ix;
	float yoffset = y - iy;
	glm::vec3 basis, first, second;
	if (xoffset > 0.5f && yoffset > 0.5f)
	{
		basis = glm::vec3(ix + 1, m_heightmap[ix + 1][iy + 1], iy + 1);
		first = glm::vec3(ix + 1, m_heightmap[ix + 1][iy - 1], iy - 1) - basis;
		second = glm::vec3(ix, m_heightmap[ix][iy + 1], iy + 1) - basis; 
		return (basis + (xoffset * first) + (yoffset * second)).y;
	}
	else
	{
		basis = glm::vec3(ix, m_heightmap[ix][iy], iy);
		first = glm::vec3(ix + 1, m_heightmap[ix + 1][iy], iy) - basis;
		second = glm::vec3(ix, m_heightmap[ix][iy+1], iy+1) - basis;
		return (basis + (xoffset * first) + (yoffset * second)).y;
	}
}