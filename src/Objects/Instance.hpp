/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.hpp
************************************
*/

#pragma once
#include "glm/glm.hpp"
#include <memory>
#include "Entity.hpp"
#include "../Graphics/IShader.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/Material.hpp"

namespace anvil
{
	class Instance
	{
	public:
		Instance(std::shared_ptr<Entity> entity, glm::vec3 &position);

		~Instance();

		void Render(IShader& shader, std::shared_ptr<Instance> i);

		/**
		* @fn	bool Instance::Update();
		*
		* @brief	Updates this instance.
		*
		* @return	returns false if the instance is invalid (should be deleted).
		*/
		bool Update();

		std::shared_ptr<Material> GetMaterial(const std::string& meshName);
		void SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state);
		void SetAnimationState(std::shared_ptr<Entity::AnimationState> state);

		inline void SetHealth(int health) { m_health = health; }
		inline void SetPosition(glm::vec3 pos) { m_position = pos; }
		inline glm::vec3 GetPosition() { return m_position; }
		inline std::shared_ptr<Entity::ModelConditionState> GetModelConditionState() { return m_modelConditionState; }
		inline std::shared_ptr<Entity::AnimationState> GetAnimationState() { return m_animationState; }

	private:
		std::shared_ptr<Entity> m_entity;
		std::weak_ptr<IModel> m_model;
		int m_health;
		glm::vec3 m_position;
		std::shared_ptr<Entity::ModelConditionState> m_modelConditionState;
		std::shared_ptr<Entity::AnimationState> m_animationState;
	};
}
