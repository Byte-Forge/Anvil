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

		/**
		* @fn	void Animation::GetOffsetMat(int pivotID, float time);
		*
		* @brief	Returns the offset mat for this animation for a specific pivot at the given time
		*
		* @param	pivotID		ID of the pivot we want the mat for
		* @param	time		the current time of the animation
		*/
		glm::mat4 GetOffsetMat(int pivotID, long long *time);
	
		inline void SetName(const std::string &name) { m_name = name; }
		inline void SetHierarchyName(const std::string &name) { m_hierarchyName = name; }
		inline void SetFrameRate(int frameRate) { m_frameRate = frameRate; }
		inline void SetNumFrames(int numFrames) { m_numFrames = numFrames; }
		inline void AddChannel(int pivot, std::unordered_map<int, std::map<int, glm::f32>> channel) { m_data.insert({ pivot, channel }); }

	private:
		std::string m_name;
		std::string m_hierarchyName;
		int m_numFrames;
		int m_frameRate; // frames / s

		//pivot -> type -> frame 
		std::unordered_map<int, std::unordered_map<int, std::map<int, glm::f32>>> m_data;

	private:
		glm::f32 GetOffsetValue(int pivotID, int type, int frame);
	};
}
