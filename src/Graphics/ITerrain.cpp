#include "ITerrain.hpp"
#include "../Core.hpp"
#include "../Math/SimplexNoise.hpp"
#include "../Math/Collision.hpp"
#include "../Math.hpp"

using namespace hpse;

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
		if (Collision::Ray_Tri_Intersect(m_vertices[m_faces[i]], m_vertices[m_faces[i + 1]], m_vertices[m_faces[i + 2]], origin, direction, &point))
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
	m_terrainMaterials = Core::GetCore()->GetResources()->GetTerrainMaterials();
	for (int i = 0; i < m_terrainMaterials.size(); i++)
		std::cout << m_terrainMaterials[i] << std::endl;

	for (unsigned int i = 0; i < m_width; i++)
	{
		std::vector<float> v;
		m_heightmap.push_back(v);

		std::vector<glm::vec3> m;
		m_materialmap.push_back(m);
		for (unsigned int j = 0; j < m_height; j++)
		{
			float value = 0.0f;
			value += SimplexNoise::scaled_octave_noise_2d(8, 0.7, 0.5, -20.0, 0.0, i / 100.0, j / 100.0); //for slightly evaluation
			float mountain = SimplexNoise::scaled_octave_noise_2d(2, 0.5, 0.1, -10.0, 20.0, i / 10.0, j / 10.0); //for mountain terrain
			if (value < 0.0)
				value = 0.0;
			if (mountain > 0.0)
				value += SimplexNoise::scaled_octave_noise_2d(8, 0.3, 0.1, 0.0, 10.0, i, j) * mountain / 10.0; //for mountains

			value += SimplexNoise::scaled_octave_noise_2d(5, 0.01, 0.1, 0.0, 2.0, i, j); //for flat terrain

			m_heightmap[i].push_back(value);

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

			m_materialmap[i].push_back({ mat1, mat2, val });
		}
	}
}

void ITerrain::ComputeNormals(std::vector<std::vector<glm::vec3>> &normals)
{
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	for (unsigned int i = 0; i < m_width; i++)
	{
		std::vector<glm::vec3> n;
		normals.push_back(n);
		for (unsigned int j = 0; j < m_height; j++)
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
	for (unsigned int i = 0; i < m_width - 1; i++)
	{
		for (unsigned int j = 0; j < m_height - 1; j++)
		{
			glm::vec3 a = { (float)i, m_heightmap[i][j], (float)j };
			glm::vec3 b = { (float)(i + 1), m_heightmap[i + 1][j], (float)j };
			glm::vec3 c = { (float)(i + 1), m_heightmap[i + 1][j + 1], (float)(j + 1) };
			glm::vec3 d = { (float)i, m_heightmap[i][j + 1], (float)(j + 1) };

			if (heightmap_changed)
			{
				m_vertices.push_back(a);
				m_vertices.push_back(b);
				m_vertices.push_back(c);

				m_vertices.push_back(a);
				m_vertices.push_back(c);
				m_vertices.push_back(d);

				m_normals.push_back(normals[i][j]);
				m_normals.push_back(normals[i + 1][j]);
				m_normals.push_back(normals[i + 1][j + 1]);

				m_normals.push_back(normals[i][j]);
				m_normals.push_back(normals[i + 1][j + 1]);
				m_normals.push_back(normals[i][j + 1]);
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
				m_materials.push_back(m_materialmap[i][j+1]);
				m_materials.push_back(m_materialmap[i+1][j+1]);
				m_materials.push_back(m_materialmap[i+1][j+1]);

				m_materials.push_back(m_materialmap[i][j+1]);
				m_materials.push_back(m_materialmap[i+1][j+1]);
				m_materials.push_back(m_materialmap[i][j+1]);
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