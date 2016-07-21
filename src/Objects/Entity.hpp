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
#include "../Graphics/Material.hpp"
#include "../Core/IResource.hpp"

namespace anvil
{
	class Instance;
	class Animation;

    /**
     * @class	Entity
     *
     * @brief	An entity is a object with visual parts to render and stats etc.
     */
	class Entity : public IResource, public std::enable_shared_from_this<Entity>
    {
	public:
		struct Properties
		{
			float scale = 1.0f;
			float speed;
			int health;

			std::string modelName;
			std::shared_ptr<IModel> model;
			std::string hierarchyPath;

			//since we want to load the materials only if the entity has instances
			std::map<std::string, std::tuple<std::string, std::shared_ptr<Material>>> materials;
		};

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
		* @enum		ANIMATION_MODE
		*
		* @brief	if an animation should loop or not
		*/
		enum ANIMATION_MODE
		{
			LOOP = 0,
			ONCE = 1,
			MANUAL = 2, //used for build animations
		};

		/**
		* @struct	Animation
		*
		* @brief	the animation of an animationState
		*/
		struct AnimationStruct
		{
			std::string animationName;
			std::shared_ptr<Animation> animation;
			float speed = 1.0f;
			ANIMATION_MODE mode;
		};

		/**
		* @struct	AnimationState
		*
		* @brief	the animation state an instance is in
		*/
		struct AnimationState
		{
			std::vector<AnimationStruct> animations;
		};

		/**
		* @struct	ModelConditionState
		*
		* @brief	a state of an Instance e.g. Default
		*/
		struct ModelConditionState
		{
			Properties properties;
			std::map<std::string, std::shared_ptr<AnimationState>> m_animationStates;
		};

		/**
		* @struct	child
		*
		* @brief	child entity of this entity
		*/
		struct Child
		{
			std::string name;
			glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
			glm::vec3 rotation = glm::vec3(0.0, 0.0, 0.0);
			float scale = 1.0f;
		};

		/**
		 * @fn	Entity::Entity();
		 *
		 * @brief	creates a new Entity object without a parent 
		 */
		Entity(std::string name);

		/**
		 * @fn	Entity::Entity(std::shared_ptr<Entity> parent);
		 *
		 * @brief	copys all parameters from the parent to the child 
		 * 			
		 * @param	parent	The parent entity of this entity
		 */
		Entity(std::string name, std::shared_ptr<Entity> parent);

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
		* @fn	void Entity::AddInstance(glm::vec3 position, glm::vec3 &euler);
		*
		* @brief	Adds an Instance to this Entity.
		*
		* @param	position	The position of the Instance
		* @param	rotation	The rotation of the Instance
		*/
		std::shared_ptr<Instance> AddInstance(const glm::vec3 &position, const glm::vec3 &euler = glm::vec3(0, 0, 0));

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

		inline void SetKindOfs(KindOf kO) { m_kindOfs = kO; }
		inline KindOf GetKindOfs() { return m_kindOfs; }
		inline void SetScale(float scale) { m_properties.scale = scale; }
		inline void SetSpeed(float speed) { m_properties.speed = speed; }
		inline float GetSpeed() { return m_properties.speed; }
		inline int GetHealth() { return m_properties.health; }
		inline void SetModel(std::string modelName) { m_properties.modelName = modelName; }
		inline void SetSklPath(std::string sklPath) { m_properties.hierarchyPath = sklPath; }
		inline void AddMaterial(std::string meshName, std::string material) { m_properties.materials.insert({ meshName, std::make_tuple(material, nullptr) }); }
		inline Properties GetProperties() { return m_properties; }
		inline void AddModelConditionState(const std::string name, std::shared_ptr<ModelConditionState> state) { m_modelConditionStates.insert({ name, state }); }
		inline void AddAnimationState(const std::string name, std::shared_ptr<AnimationState> state) { m_animationStates.insert({ name, state }); }
		inline void AddChild(Child child) { m_children.push_back(child); }
	
	private:
		std::string m_name;
		bool m_resourcesLoaded = false;

		Properties m_properties;
		KindOf m_kindOfs = KindOf();
		std::map<std::string, std::shared_ptr<ModelConditionState>> m_modelConditionStates;
		std::map<std::string, std::shared_ptr<AnimationState>> m_animationStates;
		std::vector<Child> m_children;
    };
}
