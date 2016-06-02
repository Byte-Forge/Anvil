/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.hpp
************************************
*/

#pragma once
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "Entity.hpp"
#include <memory>

namespace anvil
{
	class Material;

	/**
	* @class	Instance
	*
	* @brief	An instance of an entity object
	*/
	class Instance : public std::enable_shared_from_this<Instance>
	{
	public:
		/**
		* @fn	Instance::Instance(std::shared_ptr<Entity> entity, glm::vec3 &position);
		*
		* @brief	Default constructor.
		* @param	entity	the entity this instance is for
		* @param	position	the position of this instance
		*/
		Instance(std::shared_ptr<Entity> entity, glm::vec3 &position, glm::vec3 &euler = glm::vec3(0.0, 0.0, 0.0), float scale = 0.0f);

		/**
		* @fn	Instance::~Instance();
		*
		* @brief	Default destructor.
		*/
		~Instance();

		/**
		* @fn	void Instance::Init();
		*
		* @brief	initialize the instance with states and set start values
		*/
		void Init();

		/**
		* @fn	void Instance::Unlink();
		*
		* @brief	unlinks this instance from its model
		*/
		void Unlink();

		/**
		* @fn	bool Instance::Update();
		*
		* @brief	Updates this instance.
		*
		* @return	returns false if the instance is invalid (should be deleted).
		*/
		bool Update();

		/**
		* @fn	std::shared_ptr<Material> Instance::GetMaterial();
		*
		* @brief	returns the material for the given mesh name
		* @param	meshName	the name of the mesh we want the material for
		* @return	returns a pointer to the material
		*/
		std::shared_ptr<Material> GetMaterial(const std::string& meshName);

		/**
		* @fn	void Instance::SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state);
		*
		* @brief	sets the current ModelConditionState of this instance
		* @param	state	the new state
		*/
		void SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state);

		/**
		* @fn	void Instance::SetAnimationState(std::shared_ptr<Entity::AnimationState> state);
		*
		* @brief	sets the current AnimationState of this instance
		* @param	state	the new state
		*/
		void SetAnimationState(std::shared_ptr<Entity::AnimationState> state);

		inline void SetHealth(int health) { m_health = health; }
		inline void Move(glm::vec3 pos) { m_m = glm::translate(pos) * m_m; }
		inline void Rotate(glm::vec3 euler) { 
			Rotate(euler.x, glm::vec3(1.0, 0.0, 0.0)); 
			Rotate(euler.y, glm::vec3(0.0, 1.0, 0.0));
			Rotate(euler.z, glm::vec3(0.0, 0.0, 1.0));
		}
 		inline void Rotate(float angle, glm::vec3 axis) { m_m = glm::rotate(m_m, angle, axis); }
		inline void Scale(float scale) { m_m = m_m * glm::scale(glm::vec3(scale, scale, scale)); }
		inline void Scale(glm::vec3 scale) { m_m = m_m * glm::scale(scale); }
		inline glm::mat4 GetMatrix() { return m_m; }
		inline std::shared_ptr<Entity::ModelConditionState> GetModelConditionState() { return m_modelConditionState; }
		inline std::shared_ptr<Entity::AnimationState> GetAnimationState() { return m_animationState; }
		inline long long *GetAnimationTime() { return &m_animationTime; }
		inline bool IsAnimated() { return m_entity->GetKindOfs().ANIMATED; }
		inline bool IsUnit() { return m_entity->GetKindOfs().UNIT; }
		inline bool IsVisible() { return m_visible; }

	private:
		bool m_visible = false;
		bool m_firstUpdate = true;
		std::chrono::high_resolution_clock::time_point m_lastUpdated;
		long long m_animationTime = 0;
		std::shared_ptr<Entity> m_entity;
		int m_health;
		glm::mat4 m_m;
		std::shared_ptr<Entity::ModelConditionState> m_modelConditionState;
		std::shared_ptr<Entity::AnimationState> m_animationState;
	};
}
