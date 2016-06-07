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
		* @fn	void Animation::ApplyOffsets(std::vector<glm::mat4> &mats, const std::vector<glm::mat4> &rest_mats, const long long time);
		*
		* @brief	Returns the offset mats for this animation for a specific pivot at the given time
		*
		* @param	mats		the matrices the offsets should be applyed to
		* @param	rest_mats	the rest matrices 
		* @param	time		the current time of the animation
		*/
		void ApplyOffsets(std::vector<glm::mat4> &mats, const std::vector<glm::mat4> &rest_mats, const long long time);


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
		inline void SetFramesPerSecond(int framesPerSecond) { m_framesPerSecond = framesPerSecond; }
		inline void SetNumFrames(int numFrames) { m_numFrames = numFrames; }
		inline long long GetTotalTime() { return (m_numFrames / m_framesPerSecond) * 1000.0f; }
		inline std::string GetName() { return m_name; }
		inline std::string GetHierarchyName() { return m_hierarchyName; }

	private:
		std::string m_name;
		std::string m_hierarchyName;
		int m_numFrames;
		float m_framesPerSecond; 

		//pivot -> type -> frame 
		std::map<int, std::unordered_map<int, std::map<int, glm::f32>>> m_data;

	private:
		glm::vec3 GetTranslationOffset(int pivotID, int frame);
		glm::quat GetRotationOffset(int pivotID, int frame);
		glm::f32 GetOffsetValue(int pivotID, int type, int frame);
	};
}
