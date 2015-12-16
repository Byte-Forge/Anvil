#include "Frustum.hpp"

using namespace hpse;

void Frustum::Recalculate(glm::mat4 view, glm::mat4 proj)
{
	if (m_lastView == view && m_lastProjection == proj)
		return; // If both are equal - don't recalculate.

	// Save matrices from last calculation (this is the last)
	m_lastProjection = proj;
	m_lastView = view;

	float t;
	clip = proj * view;

	/* Extract the numbers for the RIGHT plane */
	m_frustum[0][0] = clip[0][3] - clip[0][0];
	m_frustum[0][1] = clip[1][3] - clip[1][0];
	m_frustum[0][2] = clip[2][3] - clip[2][0];
	m_frustum[0][3] = clip[3][3] - clip[3][0];

	/* Normalize the result */
	t = sqrt(m_frustum[0][0] * m_frustum[0][0] + m_frustum[0][1] * m_frustum[0][1] + m_frustum[0][2] * m_frustum[0][2]);
	m_frustum[0][0] /= t;
	m_frustum[0][1] /= t;
	m_frustum[0][2] /= t;
	m_frustum[0][3] /= t;

	/* Extract the numbers for the LEFT plane */
	m_frustum[1][0] = clip[0][3] + clip[0][0];
	m_frustum[1][1] = clip[1][3] + clip[1][0];
	m_frustum[1][2] = clip[2][3] + clip[2][0];
	m_frustum[1][3] = clip[3][3] + clip[3][0];

	/* Normalize the result */
	t = sqrt(m_frustum[1][0] * m_frustum[1][0] + m_frustum[1][1] * m_frustum[1][1] + m_frustum[1][2] * m_frustum[1][2]);
	m_frustum[1][0] /= t;
	m_frustum[1][1] /= t;
	m_frustum[1][2] /= t;
	m_frustum[1][3] /= t;

	/* Extract the BOTTOM plane */
	m_frustum[2][0] = clip[0][3] + clip[0][1];
	m_frustum[2][1] = clip[1][3] + clip[1][1];
	m_frustum[2][2] = clip[2][3] + clip[2][1];
	m_frustum[2][3] = clip[3][3] + clip[3][1];

	/* Normalize the result */
	t = sqrt(m_frustum[2][0] * m_frustum[2][0] + m_frustum[2][1] * m_frustum[2][1] + m_frustum[2][2] * m_frustum[2][2]);
	m_frustum[2][0] /= t;
	m_frustum[2][1] /= t;
	m_frustum[2][2] /= t;
	m_frustum[2][3] /= t;

	/* Extract the TOP plane */
	m_frustum[3][0] = clip[0][3] - clip[0][1];
	m_frustum[3][1] = clip[1][3] - clip[1][1];
	m_frustum[3][2] = clip[2][3] - clip[2][1];
	m_frustum[3][3] = clip[3][3] - clip[3][1];

	/* Normalize the result */
	t = sqrt(m_frustum[3][0] * m_frustum[3][0] + m_frustum[3][1] * m_frustum[3][1] + m_frustum[3][2] * m_frustum[3][2]);
	m_frustum[3][0] /= t;
	m_frustum[3][1] /= t;
	m_frustum[3][2] /= t;
	m_frustum[3][3] /= t;

	/* Extract the FAR plane */
	m_frustum[4][0] = clip[0][3] - clip[0][2];
	m_frustum[4][1] = clip[1][3] - clip[1][2];
	m_frustum[4][2] = clip[2][3] - clip[2][2];
	m_frustum[4][3] = clip[3][3] - clip[3][2];

	/* Normalize the result */
	t = sqrt(m_frustum[4][0] * m_frustum[4][0] + m_frustum[4][1] * m_frustum[4][1] + m_frustum[4][2] * m_frustum[4][2]);
	m_frustum[4][0] /= t;
	m_frustum[4][1] /= t;
	m_frustum[4][2] /= t;
	m_frustum[4][3] /= t;

	/* Extract the NEAR plane */
	m_frustum[5][0] = clip[0][3] + clip[0][2];
	m_frustum[5][1] = clip[1][3] + clip[1][2];
	m_frustum[5][2] = clip[2][3] + clip[2][2];
	m_frustum[5][3] = clip[3][3] + clip[3][2];

	/* Normalize the result */
	t = sqrt(m_frustum[5][0] * m_frustum[5][0] + m_frustum[5][1] * m_frustum[5][1] + m_frustum[5][2] * m_frustum[5][2]);
	m_frustum[5][0] /= t;
	m_frustum[5][1] /= t;
	m_frustum[5][2] /= t;
	m_frustum[5][3] /= t;

	m_updated = true;
}
