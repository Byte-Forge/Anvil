#pragma once 
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <array>

namespace hpse
{
	class Quadtree
	{
	public:
		Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel, unsigned int level = 0);
		//~Quadtree(); 

		void AddTriangle(uint32_t indices[3], glm::vec3& _v1, glm::vec3& _v2, glm::vec3& _v3); // Add a single triangle to Quadtree
		std::vector<uint32_t> GetTriangles(std::array<std::array<float, 4>, 6>& frustum); // Returns all objects to be drawn within specified area.
	private:
		glm::vec2 m_pos; // Note that y in here is z in 3D world.
		glm::vec2 m_size;
		unsigned int m_maxLevel, m_level; // We get total of 4^maxLevel nodes.
		float m_radius;

		std::vector<uint32_t> m_triangles;

		std::unique_ptr<Quadtree> m_NW;
		std::unique_ptr<Quadtree> m_NE;
		std::unique_ptr<Quadtree> m_SW;
		std::unique_ptr<Quadtree> m_SE;

		bool contains(glm::vec3& vertex);
		int SphereInFrustum(std::array<std::array<float, 4>, 6>& frustum);
		bool CubeInFrustum(std::array<std::array<float, 4>, 6>& frustum);
		std::vector<uint32_t> getAllTriangles(); // Returns all triangles without AABBvsFrustum check.
	};
}
