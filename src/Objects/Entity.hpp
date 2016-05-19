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
	class Entity : public IResource, public std::enable_shared_from_this<Entity>
    {
	public:

		/**
		* @struct	KindOf
		*
		* @brief	Values that represent the type of the entity
		*/
		struct KindOf
		{
			bool MISC = false;
			bool SHRUBBERY = false;
			bool UNIT = false;
			bool BUILDING = false;
		};

		/**
		* @struct	ModelConditionState
		*
		* @brief	a state of an Instance e.g. Default 
		*/
		struct ModelConditionState
		{
			std::string modelName;
			std::shared_ptr<IModel> model;
			std::string hierarchyPath;
			std::map<std::string, std::tuple<std::string, std::shared_ptr<Material>>> materials;
		};

		/**
		* @enum		ANIMATION_MODE
		*
		* @brief	if an animation should loop or not
		*/
		enum ANIMATION_MODE
		{
			LOOP = 0,
			ONCE = 1,
		};

		/**
		* @struct	AnimationState
		*
		* @brief	the animation state an instance is in
		*/
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

		/**
		* @fn	void Entity::Update();
		*
		* @brief	updates the instances of this entity
		*/
		void Update();

		/**
		* @fn	void Entity::AddInstance(glm::vec3 position);
		*
		* @brief	Adds an Instance to this Entity.
		*
		* @param	position	The position of the Entity.
		*/
		void AddInstance(glm::vec3 &position);

		/**
		* @fn	void Entity::LoadResources();
		*
		* @brief	loads all resources (models, textures etc.) for this entity when the first instance is created
		*/
		void LoadResources();

		/**
		* @fn	std::shared_ptr<ModelConditionState> Entity::GetModelConditionState(const std::string &name);
		*
		* @brief	returns an ModelConditionState referenced by name
		* @param	name	the name of the ConditionState 
		* @return	returns the desired state or nullptr if it does not exist
		*/
		std::shared_ptr<ModelConditionState> GetModelConditionState(const std::string &name);

		/**
		* @fn	std::shared_ptr<AnimationState> Entity::GetAnimationState(const std::string &name);
		*
		* @brief	returns an AnimationState referenced by name
		* @param	name	the name of the AnimationState 
		* @return	returns the desired state or nullptr if it does not exist
		*/
		std::shared_ptr<AnimationState> GetAnimationState(const std::string &name);

		inline int GetHealth() { return m_health; }
		inline void AddModelConditionState(const std::string name, std::shared_ptr<ModelConditionState> state) { m_modelConditionStates.insert({ toUpper(name), state }); }
		inline void AddAnimationState(const std::string name, std::shared_ptr<AnimationState> state) { m_animationStates.insert({ toUpper(name), state }); }

	private:
		bool m_resourcesLoaded = false;
		
		int m_health = 1000;
		std::map<std::string, std::shared_ptr<ModelConditionState>> m_modelConditionStates;
		std::map<std::string, std::shared_ptr<AnimationState>> m_animationStates;

		std::deque<std::shared_ptr<Instance>> m_instances;
    };
}
