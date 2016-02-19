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
#include "../Types/BF3D.hpp"

namespace anvil
{
	class IModel
	{
	public:
		IModel();
		~IModel();

		virtual void Render(int mode);
		virtual void Update();
	private:
		std::string hierarchyName; //is empty if no hierarchy is needed
		std::vector<Mesh> meshes;
		BoundingVolume volume;
	};
}