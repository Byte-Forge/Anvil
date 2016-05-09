/*
************************************
* Copyright (C) 2016 ByteForge
* Animation.cpp
************************************
*/

#include "Animation.hpp"
#include <iostream>

using namespace anvil;

Animation::Animation()
{

}

Animation::~Animation()
{

}

glm::mat4 Animation::GetOffsetMat(int pivot, float time)
{
	//add a test if the animation is over and if it should loop

	float delta = 1.0f / m_frameRate;
	int frame = time / delta;

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
				std::cout << it3->second << std::endl;
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