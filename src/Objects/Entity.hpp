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
		~Entity();


		/** @brief	The model (visual part of the entity). */
		std::shared_ptr<IModel> m_model;

		/** @brief	The materials used by the model */
		std::vector<std::shared_ptr<Material>> m_materials;
    };
}


