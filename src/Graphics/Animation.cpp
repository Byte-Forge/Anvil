/*
************************************
* Copyright (C) 2016 ByteForge
* Animation.cpp
************************************
*/

#include "Animation.hpp"
#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "../Util.hpp"

using namespace anvil;

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::ApplyOffsets(std::vector<glm::mat4> &mats, const std::vector<glm::mat4> &rest_mats, int pivotCount, long long *time)
{
	float delta = m_framesPerSecond / 1000.0f; //frames per millisecond
	int frame = *time * delta;

	for (int i = 0; i < pivotCount; i++)
	{
		glm::vec3 of = GetTranslationOffset(i, frame);

		glm::quat q = GetRotationOffset(i, frame);
		glm::quat qt = glm::toQuat(rest_mats[i]);
		qt = q;

		mats[i] = glm::toMat4(qt);

		mats[i][0][3] = rest_mats[i][0][3] + of.x;
		mats[i][1][3] = rest_mats[i][1][3] + of.y;
		mats[i][2][3] = rest_mats[i][2][3] + of.z;
	}
}

glm::vec3 Animation::GetTranslationOffset(int pivot, int frame)
{
	float x = GetOffsetValue(pivot, 0, frame);
	float y = GetOffsetValue(pivot, 1, frame);
	float z = GetOffsetValue(pivot, 2, frame);

	return glm::vec3(x, z, -y);
}

glm::quat Animation::GetRotationOffset(int pivot, int frame)
{
	float w = GetOffsetValue(pivot, 3, frame);
	float qx = GetOffsetValue(pivot, 4, frame);
	float qy = GetOffsetValue(pivot, 5, frame);
	float qz = GetOffsetValue(pivot, 6, frame);

	glm::quat q = glm::quat(w, -qx, -qz, qy);

	return q;
}

glm::f32 Animation::GetOffsetValue(int pivotID, int type, int frame)
{
	const auto& it = m_data.find(pivotID);
	if (it != m_data.end())
	{
		const auto& it2 = it->second.find(type);
		if (it2 != it->second.end())
		{
			const auto& it3 = it2->second.find(frame);
			if (it3 != it2->second.end())
			{
				return it3->second;
			}
			//else we have to interpolate between two keyframes
			else
			{
				int beforeFrame = 0;
				int afterFrame;
				glm::f32 before = it2->second.begin()->second;
				glm::f32 after;
				for (std::map<int, glm::f32>::iterator i = it2->second.begin(); i != it2->second.end(); ++i)
				{
					if (i->first < frame)
					{
						beforeFrame = i->first;
						before = i->second;
					}
					else if (i->first > frame)
					{
						afterFrame = i->first;
						after = i->second;

						float delta = afterFrame - beforeFrame;
						float ratio = (frame - beforeFrame) / delta;
						return ratio * before + (1 - ratio) * after;
					}
				}
			}
		}
	}
	return 0.0f;
}

void Animation::AddChannel(int pivot, int type, std::map<int, glm::f32> frames)
{
	const auto& it = m_data.find(pivot);
	if (it == m_data.end())
	{
		std::unordered_map<int, std::map<int, glm::f32>> channels;
		channels.insert({ type, frames});
		m_data.insert({pivot, channels});
	}
	else
	{
		m_data[pivot].insert({type, frames});
	}
}