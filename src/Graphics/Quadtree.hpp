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
		Quadtree(glm::vec2 pos, glm::vec2 size, unsigned int maxLevel = 5, unsigned int level = 0);

		void AddTriangle(uint32_t indices[3], glm::vec3& _v1, glm::vec3& _v2, glm::vec3& _v3); // Add a single triangle to Quadtree
		std::vector<uint32_t> GetTriangles(const std::array<std::array<float, 4>, 6>& frustum); // Returns all objects to be drawn within specified area.
	private:
		glm::vec3 m_pos; // Note that y in here is z in 3D world.
		glm::vec3 m_size;
		float m_top; // y value of highest vertex
		float m_bottom; // y value of lowest vertex
		unsigned int m_maxLevel, m_level; // We get total of 4^maxLevel nodes.
		float m_radius;

		std::vector<uint32_t> m_triangles;

		std::unique_ptr<Quadtree> m_NW;
		std::unique_ptr<Quadtree> m_NE;
		std::unique_ptr<Quadtree> m_SW;
		std::unique_ptr<Quadtree> m_SE;

		bool contains(glm::vec3& vertex);
		int SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum);
		bool CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum);
		std::vector<uint32_t> getAllTriangles(); // Returns all triangles without AABBvsFrustum check.
		void update(glm::vec3& v1, glm::vec3& v2, glm::vec3& v3);
	};
}
