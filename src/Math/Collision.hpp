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
	/**
	* @class	Collision
	*
	* @brief	A class for collision algorithms
	*/
	class Collision
	{
	public:


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
		 * @return	0 if not in frustum, 1 if intersects, 2 if inside frustum
		 */
		static int SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const float radius);

	};
}