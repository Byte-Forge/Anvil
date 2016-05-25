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
#include "../Util.hpp"

using namespace anvil;

Animation::Animation()
{

}

Animation::~Animation()
{

}

glm::mat4 Animation::GetOffsetMat(int pivot, long long *time)
{
	//translation * rotation * scale
	float delta = m_framesPerSecond / 1000.0f; //frames per millisecond
	int frame = *time * delta;

	float x = GetOffsetValue(pivot, 0, frame);
	float y = GetOffsetValue(pivot, 1, frame);
	float z = GetOffsetValue(pivot, 2, frame);

	float w = GetOffsetValue(pivot, 3, frame);
	float qx = GetOffsetValue(pivot, 4, frame);
	float qy = GetOffsetValue(pivot, 5, frame);
	float qz = GetOffsetValue(pivot, 6, frame);

	glm::quat q = glm::quat(w, qx, qy, qz);
	glm::mat4 r = glm::mat4_cast(q);
	glm::mat4 t = glm::mat4();

	t[0][3] = x;
	t[1][3] = y;
	t[2][3] = z;

	//std::cout << "####" << std::endl;
	//printMat4x4(t);
	//printMat4x4(r);
	//printMat4x4(t * r);

	return glm::mat4();
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
				//the searched frame is already a keyframe -> no interpolation needed?? (at constant at least?)
				return it3->second;
			}
			//else we have to interpolate between two keyframes
			else
			{
				int beforeFrame;
				int afterFrame;
				glm::f32 before;
				glm::f32 after;
				for (std::map<int, glm::f32>::iterator i = it2->second.begin(); i != it2->second.end(); ++i)
				{
					if (i->first < frame)
					{
						beforeFrame = i->first;
						before = i->second;
					}
					if (i->first > frame)
					{
						afterFrame = i->first;
						after = i->second;

						int delta = afterFrame - beforeFrame;
						float ratio = (frame - before) / delta;
						return ratio * before + (1 - ratio) * after;
					}
				}
			}
		}
	}
	return 0.0f;
}