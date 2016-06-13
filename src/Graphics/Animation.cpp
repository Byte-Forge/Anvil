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

void Animation::ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, const long long time)
{
	int frame = time * m_framesPerMilliSecond;

	const auto& it = m_poses.find(frame);
	if (it == m_poses.end())
	{
		for (int i = 0; i < m_data.size(); i++)
		{
			glm::vec4 of = glm::vec4(GetOffsetValue(i, 0, frame), GetOffsetValue(i, 1, frame), GetOffsetValue(i, 2, frame), 1.0f);
			glm::quat q = glm::quat(GetOffsetValue(i, 3, frame), GetOffsetValue(i, 4, frame), GetOffsetValue(i, 5, frame), GetOffsetValue(i, 6, frame));


			frame_mats[i] = glm::toMat4(q);
			//of *= of;

			frame_mats[i][0][3] = rest_mats[i][0][3] + of.x;
			frame_mats[i][1][3] = rest_mats[i][1][3] + of.y;
			frame_mats[i][2][3] = rest_mats[i][2][3] + of.z;
		}
		m_poses.insert({ frame, AnimationPose(frame_mats) });
	}
}

void Animation::GetFrame(std::vector<glm::mat4> &mats, const long long time)
{
	int frame = time * m_framesPerMilliSecond;

	const auto& it = m_poses.find(frame);
	if (it != m_poses.end())
	{
		mats = it->second.GetData();
		return;
	}
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