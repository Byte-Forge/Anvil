/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.hpp
************************************
*/

#pragma once
#include <string>
#include <deque>
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

		/*
		struct KindOf
		{
			bool SHRUBBERY = false;
			bool TREE = false;
			bool IMMOBILE = false;
			bool SELECTABLE = false;
			bool INFANTRY = false;
			bool PORTER = false;
		};
		*/

		struct Instance
		{
			int health;
			glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
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

		void SetModel(std::string model);
		void AddInstance(glm::vec3 position);

		inline std::shared_ptr<IModel> GetModel() { return m_model; }
		inline void AddMaterial(std::string meshName, std::shared_ptr<Material> material) { m_materials.insert({ meshName, material }); }
		inline std::shared_ptr<Material> GetMaterial(std::string meshName) { return m_materials[meshName]; }
		std::deque<std::shared_ptr<Instance>> GetInstances();

	private:
		int m_health = 1000;

		std::string m_model_string;
		std::shared_ptr<IModel> m_model;
		std::map<std::string, std::shared_ptr<Material>> m_materials;
		std::deque<std::shared_ptr<Instance>> m_instances;
    };
}
