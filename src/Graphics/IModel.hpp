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
#include <glm/glm.hpp>
#include "../Graphics/IMesh.hpp"
#include "../Core/IResource.hpp"
#include "../Graphics/IRenderable.hpp"

namespace anvil
{
	class IModel : public IResource, public IRenderable
	{
	public:
		struct BoundingVolume
		{
			glm::f32vec3 center;
		};

		struct Box : BoundingVolume
		{
			glm::f32vec3 extend;
		};

		struct Sphere : BoundingVolume
		{
			glm::float32 radius;
		};

		IModel();
		~IModel();

		std::string m_hierarchyName; //is empty if no hierarchy is needed
		std::vector<IMesh> m_meshes;
		BoundingVolume m_volume;
	private:
	
	};
}