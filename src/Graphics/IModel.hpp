/*
************************************
* Copyright (C) 2016 ByteForge
* IModel.hpp
************************************
*/

#pragma once
#include "IRenderable.hpp"
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "../Graphics/IMesh.hpp"
#include "../Core/IResource.hpp"
#include "../Graphics/IRenderable.hpp"

namespace anvil
{
	/**
	 * @class	IModel
	 *
	 * @brief	A model. Consists of one or more meshes.
	 */
	class IModel : public IResource, public IRenderable
	{
	public:

		/**
		 * @struct	BoundingVolume
		 *
		 * @brief	A bounding volume.
		 */
		struct BoundingVolume
		{
			glm::f32vec3 center;
		};

		/**
		 * @struct	Box
		 *
		 * @brief	A bounding box.
		 */
		struct Box : BoundingVolume
		{
			glm::f32vec3 extend;
		};

		/**
		 * @struct	Sphere
		 *
		 * @brief	A bounding sphere.
		 */
		struct Sphere : BoundingVolume
		{
			glm::float32 radius;
		};

		inline void SetHierarchyName(const std::string& hierarchyName) { m_hierarchyName = hierarchyName; }
		//inline void AddMesh(IMesh* mesh) { m_meshes.push_back(*mesh); } // this sux
		inline void SetBoundingVolume(BoundingVolume vol) { m_volume = vol; }

	protected:
		std::string m_hierarchyName; //is empty if no hierarchy is needed
		std::vector<IMesh> m_meshes;
		BoundingVolume m_volume;
	};
}