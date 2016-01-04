#include "Quadtree.hpp"
#include <iostream>
#include "../Math/Collision.hpp"

using namespace hpse;

Quadtree::Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel, unsigned int level) :
	m_maxLevel(maxLevel), m_level(level)
{
	m_pos = { pos.x, 0.0, pos.y };
	m_size = { size.x, 0.0, size.y };
	m_radius = glm::length(m_size);
	if (level == maxLevel)
		return;

	// Create new nodes for 4 new regions until maxLevel is reached.
	m_NW = std::make_unique<Quadtree>(glm::vec2(pos.x - size.x / 2.f, pos.y - size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_NE = std::make_unique<Quadtree>(glm::vec2(pos.x + size.x / 2.f, pos.y - size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_SW = std::make_unique<Quadtree>(glm::vec2(pos.x - size.x / 2.f, pos.y + size.y / 2.f), size / 2.f, maxLevel, level + 1);
	m_SE = std::make_unique<Quadtree>(glm::vec2(pos.x + size.x / 2.f, pos.y + size.y / 2.f), size / 2.f, maxLevel, level + 1);
}

int ne = 0;
int nw = 0;
int se = 0;
int sw = 0;

void Quadtree::AddTriangle(uint32_t indices[3], glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	if (m_level == m_maxLevel) // If max level is reached we dont bother checking for nodes.
	{
		update(v1, v2, v3);
		m_triangles.insert(m_triangles.end(), indices, indices + 3);
		return;
	}


	if (m_NW->contains(v1) && m_NW->contains(v2) && m_NW->contains(v3))
	{
		nw++;
		m_NW->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_NE->contains(v1) && m_NE->contains(v2) && m_NE->contains(v3))
	{
		ne++;
		m_NE->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_SW->contains(v1) && m_SW->contains(v2) && m_SW->contains(v3))
	{
		sw++;
		m_SW->AddTriangle(indices, v1, v2, v3);
		return;
	}
	else if (m_SE->contains(v1) && m_SE->contains(v2) && m_SE->contains(v3))
	{
		se++;
		m_SE->AddTriangle(indices, v1, v2, v3);
		return;
	}

	update(v1, v2, v3);
	m_triangles.insert(m_triangles.end(), indices, indices + 3);
}

std::vector<uint32_t> Quadtree::GetTriangles(const std::array<std::array<float, 4>, 6>& frustum)
{
	if (m_level == m_maxLevel)
		return m_triangles;

	std::vector<uint32_t> retObjects;

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
	return Collision::Contains2D(vertex, m_pos, m_size);
}

int Quadtree::SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum)
{
	return Collision::SphereInFrustum(frustum, m_pos, m_radius);
}

bool Quadtree::CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum)
{
	return Collision::CubeInFrustum(frustum, m_pos, m_size);
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

void Quadtree::update(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3)
{
	if (v1.y < m_bottom)
		m_bottom = v1.y;
	if (v1.y > m_top)
		m_top = v1.y;
	if (v2.y < m_bottom)
		m_bottom = v2.y;
	if (v2.y > m_top)
		m_top = v2.y;
	if (v3.y < m_bottom)
		m_bottom = v3.y;
	if (v3.y > m_top)
		m_top = v3.y;

	m_pos.y = (m_top + m_bottom) / 2.0;
	m_size.y = m_top - m_bottom;
	m_radius = glm::length(m_size);
}
