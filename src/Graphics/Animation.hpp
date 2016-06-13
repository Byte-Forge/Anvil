/*
************************************
* Copyright (C) 2016 ByteForge
* Animation.hpp
************************************
*/

#pragma once
#include "../Core/IResource.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>
#include "AnimationPose.hpp"

namespace anvil
{
	/**
	* @class	Animation
	*
	* @brief	The Animation of a Hierarchy
	*/
	class Animation : public IResource
	{
	public:

		/**
		* @fn	Animation::Animation();
		*
		* @brief	Default constructor.
		*/
		Animation();

		/**
		* @fn	Animation::~Animation();
		*
		* @brief	Destructor.
		*/
		~Animation();

		void ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, const long long time);

		void GetFrame(std::vector<glm::mat4> &mats, const long long time);

		/**
		* @fn	void Animation::AddChannel(int pivot, int type, std::map<int, glm::f32> frames);
		*
		* @brief	adds an animation channel to this animation
		*
		* @param	pivot		the pivot this channel is for
		* @param	type		the type of this channel
		* @param	frames		the values for the specific frames
		*/
		void AddChannel(int pivot, int type, std::map<int, glm::f32> frames);
	
		inline void SetName(const std::string &name) { m_name = name; }
		inline void SetHierarchyName(const std::string &name) { m_hierarchyName = name; }
		inline void SetFramesPerSecond(int framesPerSecond) { m_framesPerSecond = framesPerSecond; m_framesPerMilliSecond = m_framesPerSecond / 1000.0f; }
		inline void SetNumFrames(int numFrames) { m_numFrames = numFrames; }
		inline long long GetTotalTime() { return (m_numFrames / m_framesPerSecond) * 1000.0f; }
		inline std::string GetName() { return m_name; }
		inline std::string GetHierarchyName() { return m_hierarchyName; }

	private:
		std::string m_name;
		std::string m_hierarchyName;
		int m_numFrames;
		float m_framesPerSecond; 
		float m_framesPerMilliSecond;

		//pivot -> type -> frame 
		std::map<int, std::unordered_map<int, std::map<int, glm::f32>>> m_data;
		std::map<int, AnimationPose> m_poses;

	private:
		glm::f32 GetOffsetValue(int pivotID, int type, int frame);
	};
}
