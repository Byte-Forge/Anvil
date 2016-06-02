/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.cpp
************************************
*/

#include "Instance.hpp"
#include "../Exception.hpp"
#include "../Core.hpp"
#include "../Math/Collision.hpp"
#include "../Graphics/Camera.hpp"
#include "../Graphics/Frustum.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/Material.hpp"
#include "../Graphics/Animation.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "../Util.hpp"

using namespace anvil;

Instance::Instance(std::shared_ptr<Entity> entity, glm::vec3 &position, glm::vec3 &euler, float scale) : m_entity(entity)
{
	m_m = glm::mat4();
	Rotate(euler);
	Move(position);
	srand(time(NULL));
}

Instance::~Instance()
{

}

void Instance::Init()
{
	if (m_entity->GetKindOfs().BUILDING)
	{
		SetModelConditionState(m_entity->GetModelConditionState("CONSTRUCTION"));
		if (m_entity->GetKindOfs().ANIMATED)
			SetAnimationState(m_entity->GetAnimationState("CONSTRUCTION"));
	}
	else
	{
		SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
		if (m_entity->GetKindOfs().ANIMATED)
			SetAnimationState(m_entity->GetAnimationState("IDLE"));
	}
	SetHealth(m_entity->GetHealth());
}

void Instance::Unlink()
{
	if (m_modelConditionState->model != nullptr)
		m_modelConditionState->model->RemoveInstance(shared_from_this());
}

bool Instance::Update()
{
	//test if the instance is inside the frustum (visible)
	if (Collision::SphereInFrustum(Core::GetCore()->GetCamera()->GetFrustum()->GetFrustumArray(), m_m * m_modelConditionState->model->GetSphereCenter(), m_modelConditionState->model->GetSphereRadius()) > 0)
		m_visible = true;
	else
		m_visible = false;

	auto current = std::chrono::high_resolution_clock::now();
	if (m_firstUpdate)
	{
		m_lastUpdated = current;
		m_firstUpdate = false;
	}
	m_animationTime += (std::chrono::duration_cast<std::chrono::milliseconds>(current - m_lastUpdated).count());
	m_lastUpdated = current;

	if (IsAnimated())
	{
		long long totalAnimationTime = m_animationState->animation->GetTotalTime();
		if (m_animationTime > totalAnimationTime)
		{
			m_animationTime -= totalAnimationTime;
			if (m_animationState->mode != Entity::ANIMATION_MODE::LOOP)
				SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
		}
	}
	if (m_health <= 0)
		return false;
	return true;
}

void Instance::SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state)
{
	if (state == nullptr)
		return;
	if (m_modelConditionState != nullptr)
		m_modelConditionState->model->RemoveInstance(shared_from_this());
	m_modelConditionState = state;
	Scale(state->scale);
	m_modelConditionState->model->AddInstance(shared_from_this());
}

void Instance::SetAnimationState(std::shared_ptr<Entity::AnimationState> state)
{
	if (state == nullptr)
		return;
	m_animationState = state;
}

std::shared_ptr<Material> Instance::GetMaterial(const std::string& meshName)
{
	const auto& it = m_modelConditionState->materials.find(meshName);
	if (it == m_modelConditionState->materials.end())
	{
		//std::cout << "WARNING!: No material defined for mesh: " + meshName << std::endl;
		return nullptr;
	}
	return std::get<1>(it->second);
}
