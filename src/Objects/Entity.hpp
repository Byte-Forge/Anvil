/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.hpp
************************************
*/

#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Types/BF3D.hpp"
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"

namespace anvil
{
    class Entity : public IResource
    {
	public:
		Entity();
		Entity(std::shared_ptr<Entity> parent);
		~Entity();

		std::shared_ptr<BF3DModel> m_model;
		std::vector<std::shared_ptr<Material>> m_materials;
    };
}


