#pragma once
#include <glm/glm.hpp>
#include <array>
#include <vector>

#define EPSILON 0.000001

namespace hpse
{

	class Collision
	{
	public:
		/*
		tests if a vertex is within a box described by center and size
		returns true if the vertex is within the box
		*/
		static bool Contains(glm::vec3& vertex, glm::vec2& center, glm::vec2& size);
		static bool Contains(glm::vec3& vertex, glm::vec3& center, glm::vec3& size);

		/*
		tests if a cube is inside the frustum
		returns true if yes, false else
		*/
		static bool CubeInFrustum(std::array<std::array<float, 4>, 6>& frustum, glm::vec2& center, glm::vec2& size);

		/*
		tests if a sphere collides with the frustum
		returns 0 if it doesnt collide, 1 if it collides and 2 if sphere is fully within frustum
		*/
		static int SphereInFrustum(std::array<std::array<float, 4>, 6>& frustum, glm::vec2& center, float radius);

		static void ScreenPosToWorldRay(glm::vec2 mouse_pos, glm::vec3& out_origin, glm::vec3& out_direction);

		//
		static int Collision::Ray_Tri_Intersect(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 o, glm::vec3 d, float* out);
	};
}