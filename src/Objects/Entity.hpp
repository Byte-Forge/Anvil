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
#include "../Util.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/IShader.hpp"
#include "../Graphics/Animation.hpp"
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"

namespace anvil
{
	class Instance;

    /**
     * @class	Entity
     *
     * @brief	An entity is a object with visual parts to render and stats etc.
     */
    class Entity : public IResource
    {
	public:

		struct KindOf
		{
			bool MISC = false;
			bool SHRUBBERY = false;
			bool UNIT = false;
			bool BUILDING = false;
		};

		struct InstanceStruct
		{
			int health;
			glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
		};

		struct ModelConditionState
		{
			std::string modelName;
			std::shared_ptr<IModel> model;
			std::string hierarchyPath;
			std::map<std::string, std::tuple<std::string, std::shared_ptr<Material>>> materials;
		};

		enum ANIMATION_MODE
		{
			LOOP = 0,
			ONCE = 1,
		};

		struct AnimationState
		{
			std::string animationName;
			std::shared_ptr<Animation> animation;
			ANIMATION_MODE mode;
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
		void Render(IShader &shader);
		void AddInstance(std::shared_ptr<Entity> entity, glm::vec3 &position);

		/**
		* @fn	void Entity::SetModel(const std::string model);
		*
		* @brief	Sets the model string of an Entity.
		*
		* @param	name	The name of the Model.
		*/
		void SetModel(const std::string model);


		/**
		* @fn	void Entity::AddInstance(glm::vec3 position);
		*
		* @brief	Adds an Instance to this Entity.
		*
		* @param	position	The position of the Entity.
		*/
		void AddInstance(glm::vec3 position);

		void LoadResources();

		inline void SetSklPath(std::string skl_path) { m_skl_path = skl_path; }
		inline std::shared_ptr<IModel> GetModel() { return m_model; }
		inline void AddMaterial(std::string meshName, std::shared_ptr<Material> material) { m_materials.insert({ toUpper(meshName), material }); }
		std::shared_ptr<Material> GetMaterial(std::string meshName);
		std::deque<std::shared_ptr<InstanceStruct>> GetInstances();

		std::shared_ptr<ModelConditionState> GetModelConditionState(const std::string &name);
		std::shared_ptr<AnimationState> GetAnimationState(const std::string &name);

		inline int GetHealth() { return m_health; }
		inline void AddModelConditionState(const std::string name, std::shared_ptr<ModelConditionState> state) { m_modelConditionStates.insert({ toUpper(name), state }); }
		inline void AddAnimationState(const std::string name, std::shared_ptr<AnimationState> state) { m_animationStates.insert({ toUpper(name), state }); }

	private:
		bool m_resourcesLoaded = false;

		std::string m_model_string;
		std::string m_skl_path;
		std::shared_ptr<IModel> m_model;
		std::map<std::string, std::shared_ptr<Material>> m_materials;
		
		int m_health = 1000;
		std::map<std::string, std::shared_ptr<ModelConditionState>> m_modelConditionStates;
		std::map<std::string, std::shared_ptr<AnimationState>> m_animationStates;

		std::deque<std::shared_ptr<InstanceStruct>> m_instances_old;
		std::deque<std::shared_ptr<Instance>> m_instances;
    };
}
