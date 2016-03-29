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
#include <set>
#include <glm/glm.hpp>
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

		struct Instance
		{
			glm::vec4 position = glm::vec4(0.0, 0.0, 0.0, 1.0);
		};

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

		void Update();

		void SetModel(std::shared_ptr<IModel> model);
		void AddInstance(glm::vec3 position);

		inline std::shared_ptr<IModel> GetModel() { return m_model; }
		inline void AddMaterial(std::shared_ptr<Material> material) { m_materials.push_back(material); }
		//std::set<Instance> GetInstances();

	private:
		std::shared_ptr<IModel> m_model;
		std::vector<std::shared_ptr<Material>> m_materials;
		//std::set<Instance> m_instances;
    };
}


