/*
************************************
* Copyright (C) 2016 ByteForge
* Animation.hpp
************************************
*/

#pragma once
#include "../Core/IResource.hpp"
#include "../Math/Interpolate.hpp"
#include <string>
#include <map>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>
#include <mutex>
#include <memory>
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
	private:
		typedef Interpolate<int, glm::f32> Interpolate;
		typedef LinearInterpolate<int, glm::f32> InterpolateLinear;
		typedef std::shared_ptr<Interpolate> InterpolatePtr;

		inline InterpolatePtr MakeLinearInterpolate()
		{
			return std::make_shared<InterpolateLinear>();

		}
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
		* @fn	void Animation::ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, std::vector<std::int32_t> &parentIDs, const long long time);
		*
		* @brief	compute the matrices for a frame specified by time
		*
		* @param	frame_mats		the matrices that the offsets are applyed to
		* @param	rest_mats		the rest pose matrices of the hierarchy
		* @param	parentIDs		the ids needed for parenting
		* @param	time			the time that represents a frame
		*/
		void ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, std::vector<std::int32_t> &parentIDs, const long long time);

		/**
		* @fn	void Animation::GetFrame(std::vector<glm::mat4> &frame_mats, const long long time);
		*
		* @brief	returns the matrices for the frame represented by time
		*
		* @param	frame_mats		the matrices that the offsets are applyed to
		* @param	time		the time that represents a frame
		*/
		void GetFrame(std::vector<glm::mat4> &frame_mats, const long long time);

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
	
		inline void SetName(const std::string &name) 			{ m_name = name; }
		inline void SetHierarchyName(const std::string &name) 	{ m_hierarchyName = name; }
		inline void SetFramesPerSecond(int framesPerSecond) 	{ m_framesPerSecond = framesPerSecond; m_framesPerMilliSecond = m_framesPerSecond / 1000.0f; }
		inline void SetNumFrames(int numFrames) 				{ m_numFrames = numFrames; }
		inline long long GetTotalTime() 						{ return (m_numFrames / m_framesPerSecond) * 1000.0f; }
		inline std::string GetName() 							{ return m_name; }
	inline std::string GetHierarchyName() 						{ return m_hierarchyName; }

	private:
		std::string m_name;
		std::string m_hierarchyName;
		int m_numFrames;
		float m_framesPerSecond; 
		float m_framesPerMilliSecond;
		std::mutex m_poses_mutex;

		//pivot -> type -> frame 
		std::map<int, std::unordered_map<int, InterpolatePtr>> m_data;
		std::map<int, AnimationPose> m_poses;

	private:
		glm::f32 GetOffsetValue(int pivotID, int type, int frame);
	};
}
