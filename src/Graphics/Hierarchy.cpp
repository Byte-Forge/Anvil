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

void Hierarchy::Update(std::shared_ptr<Animation> ani, long long *time)
{
	//additionally apply the frame offsets here
	for (int i = 0; i < m_pivotCount; i++)
	{
		std::int32_t parentID = m_parentIDs[i];
		m_frame_pivots[i] = m_pivots[i];
		if (ani != nullptr)
		{
			ani->GetOffsetMat(i, time);
		}
		while (parentID >= 0)
		{
			m_frame_pivots[i] = m_frame_pivots[i] * m_pivots[parentID];
			parentID = m_parentIDs[parentID];
		}
	}
}
