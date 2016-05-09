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

		glm::mat4 GetOffsetMat(int pivotID, float time);
		glm::f32 GetOffsetValue(int pivotID, int type, int frame);

		inline void SetName(const std::string &name) { m_name = name; }
		inline void SetHierarchyName(const std::string &name) { m_hierarchyName = name; }
		inline void InsertKey(int pivot, int type, int frame, glm::f32 value) { m_data.insert({  }); }

	private:
		std::string m_name;
		std::string m_hierarchyName;
		int m_numFrames;
		int m_frameRate; // frames / s

		//pivot -> type -> frame 
		std::unordered_map<int, std::unordered_map<int, std::map<int, glm::f32>>> m_data;
	};
}
