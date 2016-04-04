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
		 * @fn	inline std::array<std::array<float, 4>, 6> Frustum::GetFrustumArray()
		 *
		 * @brief	Gets frustum array.
		 *
		 * @return	The frustum array.
		 */
		inline std::array<std::array<float, 4>, 6> GetFrustumArray()
		{
			m_updated = false;
			return m_frustum;
		}

		/**
		 * @fn	inline bool Frustum::Updated()
		 *
		 * @brief	Updated this object.
		 *
		 * @return	true if Frustum changed since last GetFrustumArray call. Should be sufficient for now.
		 */
		inline bool Updated()
		{
			return m_updated;
		}

		/**
		 * @fn	void Frustum::Recalculate(glm::mat4 view, glm::mat4 proj);
		 *
		 * @brief	Recalculates the frustum.
		 *
		 * @param	view	The view matrix.
		 * @param	proj	The project matrix.
		 */
		void Recalculate(glm::mat4 view, glm::mat4 proj);
	private:
		glm::mat4 m_lastView;
		glm::mat4 m_lastProjection;
		glm::mat4 m_clip;
		bool m_updated;
		std::array<std::array<float, 4>, 6> m_frustum; 
	};
}