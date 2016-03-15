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
#include "../Graphics/IModel.hpp"
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"

namespace anvil
{
    /**
     * @class	Entity
     *
     * @brief	An entity is a object with visual parts to render and stats etc.
     */

    class Entity : public IResource
    {
	public:

		/**
		 * @fn	Entity::Entity();
		 *
		 * @brief	creates a new Entity object without a parent 
		 */
		Entity();

		/**
		 * @fn	Entity::Entity(std::shared_ptr<Entity> parent);
		 *
		 * @brief	copys all parameters from the parent to the child 
		 * 			
		 * @param	parent	The parent entity of this entity
		 */
		Entity(std::shared_ptr<Entity> parent);

		/**
		 * @fn	Entity::~Entity();
		 *
		 * @brief	Destructor.
		 */
		~Entity();

		inline void SetModel(std::shared_ptr<IModel> model) { m_model = model; }
		inline std::shared_ptr<IModel> GetModel() { return m_model; }
		inline void AddMaterial(std::shared_ptr<Material> material) { m_materials.push_back(material); }

	private:
		std::shared_ptr<IModel> m_model;
		std::vector<std::shared_ptr<Material>> m_materials;
    };
}


