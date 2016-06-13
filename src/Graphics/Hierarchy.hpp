/*
************************************
* Copyright (C) 2016 ByteForge
* Hierarchy.hpp
************************************
*/

#pragma once
#include "../Core/IResource.hpp"
#include <string>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace anvil
{
	class Animation;

	/**
	* @class	Hierarchy
	*
	* @brief	A hierarchy. Consists of one or more pivots.
	*/
	class Hierarchy : public IResource
	{
	public:

		/**
		* @fn	Hierarchy::Hierarchy();
		*
		* @brief	Default constructor.
		*/
		Hierarchy();

		/**
		* @fn	Hierarchy::~Hierarchy();
		*
		* @brief	Default Destructor.
		*/
		~Hierarchy();

		void ComputeFrame(std::shared_ptr<Animation> ani = nullptr, const long long time = 0);

		std::vector<glm::f32mat4x4> GetPivots(std::shared_ptr<Animation> ani = nullptr, const long long time = 0);

		inline void SetName(std::string name) { m_name = name; }
		inline std::string GetName() { return m_name; }
		inline void SetPivotCount(int pivotCount) { m_pivotCount = pivotCount; }
		inline int GetPivotCount() { return m_pivotCount; }
		inline void SetCenterPos(glm::vec3 centerPos) { m_centerPos = centerPos; }
		inline glm::vec3 GetCenterPos() { return m_centerPos; }
		inline void AddParentID(std::int32_t ID) { m_parentIDs.push_back(ID); }
		inline void AddPivot(glm::f32mat4x4 pivot) { m_rest_pivots.push_back(pivot); m_pivots.push_back(pivot); m_frame_pivots.push_back(pivot); }

	private:
		std::string m_name;
		int m_pivotCount;
		glm::vec3 m_centerPos;
		std::vector<std::int32_t> m_parentIDs;
		std::vector<glm::f32mat4x4> m_rest_pivots; //pivots of the rest pose (the raw data)
		std::vector<glm::f32mat4x4> m_frame_pivots; //pivots with their frame offsets
		std::vector<glm::f32mat4x4> m_pivots; //the pivots for the current frame
	};
}