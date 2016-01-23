//
// Created by michael on 19.11.15.
//
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Types/W4D.hpp"
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"
#include "../Graphics/IRenderable.hpp"


namespace hpse
{
    class Entity : public IResource, public IRenderable
    {
	public:
		Entity();
		~Entity();

		void Render(int mode);
		void Update();

		bool Load(const std::string& path);
	private:
		std::shared_ptr<W4DModel> m_model;
		std::vector<std::shared_ptr<Material>> m_materials;
    };
}


