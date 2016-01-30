#include "ITerrain.hpp"
#include "../Core.hpp"
#include "../Math/SimplexNoise.hpp"
#include "../Math.hpp"
using namespace hpse;

ITerrain::ITerrain(std::uint32_t width, std::uint32_t height) : m_width(width),m_height(height)
{
}

void ITerrain::SetTerrainHeight(glm::vec3 & pos, float height, float radius)
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

void ITerrain::Generate()
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
			float mountain = SimplexNoise::scaled_octave_noise_2d(2, 0.5, 0.1, -10.0, 20.0, i / 10.0, j / 10.0); //for mountain terrain
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

void ITerrain::ComputeNormals(std::vector<glm::vec3> &normals)
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
				c = { i + 1, m_heightmap[index + m_width + 1], j + 1 };
				normal += Math::ComputeNormal(a, b, c);
			}
			if (i > 0 && j > 0)
			{
				b = { i, m_heightmap[index - m_width], j - 1 };
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

void ITerrain::UpdateBufferData()
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

				m_normals.push_back(normals[i + j * m_width]);
				m_normals.push_back(normals[i + 1 + j * m_width]);
				m_normals.push_back(normals[i + 1 + (j + 1) * m_width]);

				m_normals.push_back(normals[i + j*m_width]);
				m_normals.push_back(normals[i + 1 + (j + 1)*m_width]);
				m_normals.push_back(normals[i + (j + 1)*m_width]);
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