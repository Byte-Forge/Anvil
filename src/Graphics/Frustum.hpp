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
	//TODO: use glm for m_frustum
	class Frustum
	{
	public:
		inline std::array<std::array<float, 4>, 6> GetFrustumArray()
		{
			m_updated = false;
			return m_frustum;
		}
		// Returns true if Frustum changed since last GetFrustumArray call. Should be sufficient for now.
		inline bool Updated()
		{
			return m_updated;
		}
		void Recalculate(glm::mat4 view, glm::mat4 proj);
	private:
		glm::mat4 m_lastView;
		glm::mat4 m_lastProjection;
		glm::mat4 m_clip;
		bool m_updated;
		std::array<std::array<float, 4>, 6> m_frustum; // 6 planes, each described by point and normal in this order: NEAR, FAR, TOP, BOTTOM, LEFT, RIGHT 
	};
}