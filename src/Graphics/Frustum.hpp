/*
************************************
* Copyright (C) 2016 ByteForge
* Frustum.hpp
************************************
*/

#pragma once
#include <array>
#include <glm/glm.hpp>

namespace anvil
{
	/**
	 * @class	Frustum
	 *
	 * @brief	A frustum.
	 * 			
	 * @TODO: use glm for the frustum
	 */
	class Frustum
	{
	public:

		/**
		* @fn	void Frustum::Recalculate(glm::mat4 view, glm::mat4 proj);
		*
		* @brief	Recalculates the frustum.
		*
		* @param	view	The view matrix.
		* @param	proj	The project matrix.
		*/
		void Recalculate(glm::mat4 view, glm::mat4 proj);

		inline std::array<std::array<float, 4>, 6> GetFrustumArray() { m_updated = false; return m_frustum; }
		inline bool Updated() { return m_updated; }

	private:
		glm::mat4 m_lastView;
		glm::mat4 m_lastProjection;
		glm::mat4 m_clip;
		bool m_updated;
		std::array<std::array<float, 4>, 6> m_frustum; 
	};
}