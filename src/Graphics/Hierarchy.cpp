/*
************************************
* Copyright (C) 2016 ByteForge
* Hierarchy.cpp
************************************
*/

#include "Hierarchy.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Animation.hpp"

using namespace anvil;

Hierarchy::Hierarchy()
{

}

Hierarchy::~Hierarchy()
{

}

void Hierarchy::ComputeFrame(std::shared_ptr<Animation> ani, const long long time)
{
	ani->ComputeFrame(m_frame_pivots, m_rest_pivots, m_parentIDs, time);
}

std::vector<glm::f32mat4x4> Hierarchy::GetPivots(std::shared_ptr<Animation> ani, const long long time)
{
	if (ani != nullptr)
	{
		ani->GetFrame(m_frame_pivots, time);
		return m_frame_pivots;
	}

	//do this only once for hierarchies with no animation
	/*
	for (int i = 0; i < m_pivotCount; i++)
	{
		std::int32_t parentID = m_parentIDs[i];
		m_pivots[i] = m_frame_pivots[i];

		//do the parenting
		while (parentID >= 0)
		{
			m_pivots[i] = m_pivots[i] * m_frame_pivots[parentID];
			parentID = m_parentIDs[parentID];
		}
		m_pivots[i] = glm::transpose(m_pivots[i]);
	}
	*/
	return m_pivots;
}
