/*
************************************
* Copyright (C) 2016 ByteForge
* Frustum.cpp
************************************
*/

#include "Frustum.hpp"
#include <iostream>

using namespace anvil;

void Frustum::Recalculate(glm::mat4 view, glm::mat4 proj)
{
	if (m_lastView == view && m_lastProjection == proj)
	{
		return; // If both are equal - don't recalculate.
	}
	// Save matrices from last calculation (this is the last)
	m_lastProjection = proj;
	m_lastView = view;

	float t;
	m_clip = proj * view;

	/* Extract the numbers for the RIGHT plane */
	m_frustum[RIGHT] = glm::vec4(m_clip[0][3] - m_clip[0][0],
						m_clip[1][3] - m_clip[1][0],
						m_clip[2][3] - m_clip[2][0],
						m_clip[3][3] - m_clip[3][0]);

	/* Extract the numbers for the LEFT plane */
	m_frustum[LEFT] = glm::vec4(m_clip[0][3] + m_clip[0][0],
						m_clip[1][3] + m_clip[1][0],
						m_clip[2][3] + m_clip[2][0],
						m_clip[3][3] + m_clip[3][0]);


	/* Extract the BOTTOM plane */
	m_frustum[BOTTOM] = glm::vec4(m_clip[0][3] + m_clip[0][1],
						m_clip[1][3] + m_clip[1][1],
						m_clip[2][3] + m_clip[2][1],
						m_clip[3][3] + m_clip[3][1]);

	/* Extract the TOP plane */
	m_frustum[TOP] = glm::vec4(m_clip[0][3] - m_clip[0][1],
						m_clip[1][3] - m_clip[1][1],
						m_clip[2][3] - m_clip[2][1],
						m_clip[3][3] - m_clip[3][1]);


	/* Extract the FAR plane */
	m_frustum[FAR] = glm::vec4(m_clip[0][3] - m_clip[0][2],
						m_clip[1][3] - m_clip[1][2],
						m_clip[2][3] - m_clip[2][2],
						m_clip[3][3] - m_clip[3][2]);


	/* Extract the NEAR plane */
	m_frustum[NEAR] = glm::vec4(m_clip[0][3] + m_clip[0][2],
						m_clip[1][3] + m_clip[1][2],
						m_clip[2][3] + m_clip[2][2],
						m_clip[3][3] + m_clip[3][2]);

	/* Normalize the result */
	for (auto& plane : m_frustum)
	{
		float length = glm::length(glm::vec3(plane));
		plane /= length;
	}

	m_updated = true;
}
