/*
************************************
* Copyright (C) 2016 ByteForge
* AnimationPose.hpp
************************************
*/

#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace anvil
{
	/**
	* @class	AnimationPose
	*
	* @brief	A AnimationPose of an Animation at a specific frame
	*/
	class AnimationPose
	{
	public:

		/**
		* @fn	AnimationPose::AnimationPose();
		*
		* @brief	Default constructor.
		*/
		AnimationPose(std::vector<glm::mat4> &data);

		/**
		* @fn	AnimationPose::~AnimationPose();
		*
		* @brief	Destructor.
		*/
		~AnimationPose();

		inline std::vector<glm::mat4> GetData() { return m_data; }

	private:
		int m_count; //number of instances that use this pose per frame
		std::vector<glm::f32mat4x4> m_data;
	};
}