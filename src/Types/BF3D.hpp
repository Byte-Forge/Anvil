/*
************************************
* Copyright (C) 2016 ByteForge
* BF3D.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Core/IResource.hpp"
#include <stdint.h>

namespace anvil
{
	//#######################################################################################
	//# animation
	//#######################################################################################

	// chunk 513
	struct AnimationHeader
	{
		std::string name;
		std::string hieraName;
		std::int32_t numFrames;
		std::int32_t frameRate;
	};

	struct TimeCodedAnimationKey
	{
		std::uint16_t frame;
	};

	struct TimeCodedAnimationFloatKey : TimeCodedAnimationKey
	{
		glm::float32 value;
	};

	struct TimeCodedAnimationQuatKey : TimeCodedAnimationKey
	{
		glm::f32vec4 value; // use quat here instead ?
	};

	// chunk 514
	struct TimeCodedAnimationChannel
	{
		std::uint16_t vectorLen;
		std::int8_t type;
		std::uint16_t pivot;
		std::vector<TimeCodedAnimationKey> timeCodedKeys;
	};

	// chunk 512
	class Animation 
	{
	public:
		AnimationHeader header;
		std::vector<TimeCodedAnimationChannel> channels;
	};
}
