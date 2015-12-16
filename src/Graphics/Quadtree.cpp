#include "Quadtree.hpp"
#include <iostream>

using namespace hpse;

Quadtree::Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel, unsigned int level) :
	m_pos(pos), m_size(size), m_maxLevel(maxLevel), m_level(level)
{
	m_radius = size.x;// glm::length(m_size);
	if (level == maxLevel)
		return;

	// Create new nodes for 4 new regions until maxLevel is reached.
	m_NW = std::make_unique<Quadtree>(glm::vec2(pos.x - size.x / 2.f, pos.y - size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_NE = std::make_unique<Quadtree>(glm::vec2(pos.x + size.x / 2.f, pos.y - size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_SW = std::make_unique<Quadtree>(glm::vec2(pos.x - size.x / 2.f, pos.y + size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_SE = std::make_unique<Quadtree>(glm::vec2(pos.x + size.x / 2.f, pos.y + size.y / 2.f), size / 2.f, maxLevel, level + 1);
}

void Quadtree::AddTriangle(uint32_t indices[3], glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	if (m_level == m_maxLevel) // If max level is reached we dont bother checking for nodes.
	{
		m_triangles.insert(m_triangles.end(), indices, indices + 3);
		return;
	}

	if (m_NW->contains(v1) && m_NW->contains(v2) && m_NW->contains(v3))
	{
		m_NW->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_NE->contains(v1) && m_NE->contains(v2) && m_NE->contains(v3))
	{
		m_NE->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_SW->contains(v1) && m_SW->contains(v2) && m_SW->contains(v3))
	{
		m_SW->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_SE->contains(v1) && m_SE->contains(v2) && m_SE->contains(v3))
	{
		m_SE->AddTriangle(indices, v1, v2, v3);
		return;
	}

	m_triangles.insert(m_triangles.end(), indices, indices + 3);
}

std::vector<uint32_t> Quadtree::GetTriangles(std::array<std::array<float, 4>, 6>& frustum)
{
	if (m_level == m_maxLevel)
		return m_triangles;

	std::vector<uint32_t> retObjects;

	//Is sphere based on node's square within frustum? Consider changing.
	int frustumCheck = m_NW->SphereInFrustum(frustum);
	if (frustumCheck == 2)
	{
		std::vector<uint32_t> childObjects = m_NW->getAllTriangles();
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}
	else if (frustumCheck == 1 && m_NW->CubeInFrustum(frustum))
	{
		std::vector<uint32_t> childObjects = m_NW->GetTriangles(frustum);
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}

	frustumCheck = m_NE->SphereInFrustum(frustum);
	if (frustumCheck == 2)
	{
		std::vector<uint32_t> childObjects = m_NE->getAllTriangles();
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}
	else if (frustumCheck == 1 && m_NE->CubeInFrustum(frustum))
	{
		std::vector<uint32_t> childObjects = m_NE->GetTriangles(frustum);
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}

	frustumCheck = m_SW->SphereInFrustum(frustum);
	if (frustumCheck == 2)
	{
		std::vector<uint32_t> childObjects = m_SW->getAllTriangles();
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}
	else if (frustumCheck == 1 && m_SW->CubeInFrustum(frustum))
	{
		std::vector<uint32_t> childObjects = m_SW->GetTriangles(frustum);
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}

	frustumCheck = m_SE->SphereInFrustum(frustum);
	if (frustumCheck == 2)
	{
		std::vector<uint32_t> childObjects = m_SE->getAllTriangles();
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}
	else if (frustumCheck == 1 && m_SE->CubeInFrustum(frustum))
	{
		std::vector<uint32_t> childObjects = m_SE->GetTriangles(frustum);
		retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());
	}

	if (!m_triangles.empty())
		retObjects.insert(retObjects.end(), m_triangles.begin(), m_triangles.end());

	return retObjects;
}

bool Quadtree::contains(glm::vec3& vertex)
{
	return (vertex.x >= m_pos.x - m_size.x
		&& vertex.x <= m_pos.x + m_size.x
		&& vertex.z >= m_pos.y - m_size.y
		&& vertex.z <= m_pos.y + m_size.y);
}

int Quadtree::SphereInFrustum(std::array<std::array<float, 4>, 6>& frustum)
{
	// 0 if it doesnt collide, 1 if collides and 2 if AABB is fully within frustum
	int p;
	int c = 0;
	float d;


	for (p = 0; p < 6; p++)
	{
		d = frustum[p][0] * m_pos.x + frustum[p][2] * m_pos.y + frustum[p][3];
		if (d <= -m_radius)
			return 0;
		if (d > m_radius)
			c++;
	}
	return (c == 6) ? 2 : 1;
}

bool Quadtree::CubeInFrustum(std::array<std::array<float, 4>, 6>& frustum)
{
	for (int p = 0; p < 6; p++)
	{
		if (frustum[p][0] * (m_pos.x - m_size.x) + frustum[p][2] * (m_pos.y - m_size.y) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (m_pos.x + m_size.x) + frustum[p][2] * (m_pos.y - m_size.y) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (m_pos.x - m_size.x) + frustum[p][2] * (m_pos.y + m_size.y) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (m_pos.x + m_size.x) + frustum[p][2] * (m_pos.y + m_size.y) + frustum[p][3] > 0)
			continue;
		return false;
	}
	return true;
}

std::vector<uint32_t> Quadtree::getAllTriangles()
{
	if (m_level == m_maxLevel)
	{
		return m_triangles;
	}

	std::vector<uint32_t> retObjects, childObjects;
	childObjects = m_NW->getAllTriangles();
	retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());

	childObjects = m_NE->getAllTriangles();
	retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());

	childObjects = m_SW->getAllTriangles();
	retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());

	childObjects = m_SE->getAllTriangles();
	retObjects.insert(retObjects.end(), childObjects.begin(), childObjects.end());

	retObjects.insert(retObjects.end(), m_triangles.begin(), m_triangles.end());

	return retObjects;
}
