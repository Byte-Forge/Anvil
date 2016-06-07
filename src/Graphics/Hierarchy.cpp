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
	if (ani != nullptr)
	{
		if (ani->GetHierarchyName() == m_name)
		{
			ani->ApplyOffsets(m_frame_pivots, m_rest_pivots, time);
		}
		else
		{
			std::cout << "WARNING!! the animation: " << ani->GetName() << " is not compatible with the skeleton: " << m_name << std::endl;
		}
	}

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
		m_pivots[i] = glm::transpose(m_pivots[i]); //can we do this on file export already?
	}
}
