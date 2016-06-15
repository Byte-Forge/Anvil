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

void Animation::ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, std::vector<std::int32_t> &parentIDs, const long long time)
{
	int frame = time * m_framesPerMilliSecond;

	m_poses_mutex.lock();
	const auto& it = m_poses.find(frame);
	m_poses_mutex.unlock();
	if (it == m_poses.end())
	{
		std::vector<glm::mat4> mats;
		for (int i = 0; i < rest_mats.size(); i++)
		{
			glm::vec4 of = glm::vec4(GetOffsetValue(i, 0, frame), GetOffsetValue(i, 1, frame), GetOffsetValue(i, 2, frame), 1.0f);
			glm::quat q = glm::quat(GetOffsetValue(i, 3, frame), GetOffsetValue(i, 4, frame), GetOffsetValue(i, 5, frame), GetOffsetValue(i, 6, frame));

			mats.push_back(glm::toMat4(q));
			//of *= of;

			mats[i][0][3] = rest_mats[i][0][3] + of.x;
			mats[i][1][3] = rest_mats[i][1][3] + of.y;
			mats[i][2][3] = rest_mats[i][2][3] + of.z;
		}

		//do the parenting
		std::vector<glm::mat4> pivots;
		for (int i = 0; i < rest_mats.size(); i++)
		{
			std::int32_t parentID = parentIDs[i];
			pivots.push_back(mats[i]);

			//do the parenting
			while (parentID >= 0)
			{
				mats[i] = mats[i] * pivots[parentID];
				parentID = parentIDs[parentID];
			}
			mats[i] = glm::transpose(mats[i]);
		}
		m_poses_mutex.lock();
		const auto& it2 = m_poses.find(frame);
		if (it == m_poses.end())
			m_poses.insert({ frame, AnimationPose(mats) });
		m_poses_mutex.unlock();
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
			return it2->second->GetPoint(frame%m_numFrames);
		}
	}
	return 0.0f;
}

void Animation::AddChannel(int pivot, int type, std::map<int, glm::f32> frames)
{
	const auto& it = m_data.find(pivot);
	if (it == m_data.end())
	{
		std::unordered_map<int, AniInterpolate> channels;
		AniInterpolate interpolate = std::make_shared<LinearInterpolate<int,glm::f32>>();
		for(const auto& frame : frames)
		{

			interpolate->AddPoint(frame.first,frame.second);
		}
		channels.insert({ type, interpolate});
		m_data.insert({pivot, channels});
	}
	else
	{
		AniInterpolate interpolate = std::make_shared<LinearInterpolate<int,glm::f32>>();
		for(const auto& frame : frames)
		{
			interpolate->AddPoint(frame.first,frame.second);
		}
		m_data[pivot].insert({type, interpolate});
	}
}