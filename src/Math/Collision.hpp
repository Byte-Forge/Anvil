/*
************************************
* Copyright (C) 2016 ByteForge
* Collision.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <array>
#include <vector>

#define EPSILON 0.000001

namespace anvil
{

	class Collision
	{
	public:

		/**
		 * @fn	static bool Collision::Contains2D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size);
		 *
		 * @brief	Check if 2-dimensional vertex is in a rectangle
		 *
		 * @param	vertex	The vertex.
		 * @param	center	The center.
		 * @param	size  	The size.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		static bool Contains2D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size);

		/**
		 * @fn	static bool Collision::Contains3D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size);
		 *
		 * @brief	Check if 3-dimensional vertex is in a box
		 *
		 * @param	vertex	The vertex.
		 * @param	center	The center.
		 * @param	size  	The size.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		static bool Contains3D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size);

		/**
		 * @fn	static bool Collision::CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const glm::vec3& size);
		 *
		 * @brief	Check if a cube is inside the frustum
		 *
		 * @param	frustum	The frustum.
		 * @param	center 	The center.
		 * @param	size   	The size.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		static bool CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const glm::vec3& size);

		/**
		 * @fn	static int Collision::SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const float radius);
		 *
		 * @brief	Check if a sphere is inside the frustum
		 *
		 * @param	frustum	The frustum.
		 * @param	center 	The center.
		 * @param	radius 	The radius.
		 *
		 * @return	An int.
		 */
		static int SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const float radius);


		/**
		 * @fn	static int Collision::Ray_Tri_Intersect(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& o, const glm::vec3& d, glm::vec3& point);
		 *
		 * @brief	Check if a ray intersects with a triangle
		 *
		 * @param	v1			 	The first vector of the triangle
		 * @param	v2			 	The second vector of the triangle
		 * @param	v3			 	The third vector of the triangle
		 * @param	o			 	The ray origin
		 * @param	d			 	The ray direction
		 * @param [in,out]	point	The point where the intersection happens.
		 *
		 * @return	An int.
		 */
		static int Ray_Tri_Intersect(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, 
									const glm::vec3& o, const glm::vec3& d, glm::vec3& point);
	};
}