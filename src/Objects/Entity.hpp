//
// Created by michael on 19.11.15.
//
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Types/BF3D.hpp"
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"
#include "../Graphics/IRenderable.hpp"


namespace hpse
{
    class Entity : public IResource, public IRenderable
    {
	public:
		Entity();
		Entity(std::shared_ptr<Entity> parent);
		~Entity();

		void Render(int mode);
		void Update();

		std::shared_ptr<BF3DModel> m_model;
		std::vector<std::shared_ptr<Material>> m_materials;
    };
}


