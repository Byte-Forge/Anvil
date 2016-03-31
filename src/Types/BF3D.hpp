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
	//# basic structs
	//#######################################################################################

	struct RGBA
	{
		std::uint8_t r, g, b, a;
	};

	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	// chunk 257
	struct HierarchyHeader
	{
		std::string name;
		std::uint32_t pivotCount;
		glm::f32vec3 centerPos;
	};

	// chunk 258
	struct HierarchyPivot
	{
		std::string name;
		std::uint16_t parentID;
		std::uint8_t isBone;
		glm::f32vec3 position;
		glm::f32vec4 rotation; //use quat here instead??
	};

	// chunk 256
	class Hierarchy : public IResource
	{
	public:
		HierarchyHeader header;
		std::vector<HierarchyPivot> pivots;
	};

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
