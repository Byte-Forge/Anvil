/*
************************************
* Copyright (C) 2016 ByteForge
* Math.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>

namespace anvil
{
	/**
	 * @class	Math
	 *
	 * @brief	A mathematics.
	 */
	class Math
	{
	public:

		/**
		 * @fn	static glm::vec3 Math::ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c);
		 *
		 * @brief	Calculates the normal.
		 * 			
		 * @param [in,out]	a	The glm::vec3 to process.
		 * @param [in,out]	b	The glm::vec3 to process.
		 * @param [in,out]	c	The glm::vec3 to process.
		 *
		 * @return	The calculated normal.
		 */
		static glm::vec3 ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c);
	};
}