/*
************************************
* Copyright (C) 2016 ByteForge
* AnimationPose.cpp
************************************
*/

#include "AnimationPose.hpp"

using namespace anvil;

AnimationPose::AnimationPose(std::vector<glm::mat4> &data)
{
	m_data = data;
}

AnimationPose::~AnimationPose()
{

}