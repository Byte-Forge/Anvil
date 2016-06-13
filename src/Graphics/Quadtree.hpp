/*
************************************
* Copyright (C) 2016 ByteForge
* Quadtree.hpp
************************************
*/

#pragma once 
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <array>

namespace anvil
{
	/**
	 * @class	Quadtree
	 *
	 * @brief	A quadtree.
	 */
	class Quadtree
	{
	public:

		/**
		 * @fn	Quadtree::Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel = 4, unsigned int level = 0);
		 *
		 * @brief	Constructor.
		 *
		 * @param	pos			The position.
		 * @param	size		The size.
		 * @param	maxLevel	The maximum level.
		 * @param	level   	The level.
		 */
		Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel = 4, unsigned int level = 0);

		/**
		 * @fn	void Quadtree::AddTriangle(uint32_t indices[3], glm::vec3& _v1, glm::vec3& _v2, glm::vec3& _v3);
		 *
		 * @brief	Add a single triangle to Quadtree
		 *
		 * @param	indices	   	The indices.
		 * @param [in,out]	_v1	The first v.
		 * @param [in,out]	_v2	The second v.
		 * @param [in,out]	_v3	The third v.
		 */
		void AddTriangle(uint32_t indices[3], glm::vec3& _v1, glm::vec3& _v2, glm::vec3& _v3); 

		/**
		 * @fn	std::vector<uint32_t> Quadtree::GetTriangles(const std::array<std::array<float, 4>, 6>& frustum);
		 *
		 * @brief	Gets the triangles.
		 *
		 * @param	frustum	The frustum.
		 *
		 * @return	Returns all triangles to be drawn within specified area.
		 */
		std::vector<uint32_t> GetTriangles(const std::array<std::array<float, 4>, 6>& frustum); 

	private:
		glm::vec3 m_pos; 
		glm::vec3 m_size;
		float m_top = 0.0f; // y value of highest vertex
		float m_bottom = 0.0f; // y value of lowest vertex
		unsigned int m_maxLevel, m_level; // We get total of 4^maxLevel nodes.
		float m_radius;

		std::vector<uint32_t> m_triangles;

		std::array<std::unique_ptr<Quadtree>,4> m_nodes;
	private:
		bool contains(glm::vec3& vertex);
		int SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum);
		bool CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum);
		std::vector<uint32_t> getAllTriangles(); // Returns all triangles without AABBvsFrustum check.
		void update(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	};
}
