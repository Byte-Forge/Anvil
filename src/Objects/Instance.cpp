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
#include "../Graphics/Hierarchy.hpp"
#include "../Types/Map.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "../Util.hpp"

using namespace anvil;

Instance::Instance(std::shared_ptr<Entity> entity, const glm::vec3 &position, const glm::vec3 &euler, const float scale) : m_entity(entity)
{
	m_m = glm::mat4();
	SetPosition(position);
	Rotate(euler);
	std::srand(time(NULL));
}

Instance::~Instance()
{
	Unlink();
}

void Instance::Init()
{
	if (m_entity->GetKindOfs().BUILDING)
	{
		SetModelConditionState(m_entity->GetModelConditionState("CONSTRUCTION"));
		SetAnimationState(m_entity->GetAnimationState("CONSTRUCTION"));
	}
	else
	{
		SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
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
	auto current = std::chrono::high_resolution_clock::now();
	if (m_firstUpdate)
	{
		Init();
		m_lastUpdated = current;
		m_firstUpdate = false;
		if (IsAnimated())
			m_animationTime = std::rand() % 2000; //to add some varation to unit animations
	}
	m_deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(current - m_lastUpdated).count();
	m_lastUpdated = current;

	//test if the instance is inside the frustum (visible)
	if (Collision::SphereInFrustum(
		Core::GetCore()->GetCamera()->GetFrustum()->GetFrustumArray(),
		glm::vec3(m_m * m_modelConditionState->model->GetSphereCenter()),
		m_modelConditionState->model->GetSphereRadius() * m_modelConditionState->scale) > 0)
	{
		m_visible = true;
		if (IsAnimated())
			m_modelConditionState->model->GetHierarchy()->ComputeFrame(m_animationState->animations[m_animationIndex].animation, m_animationTime);
	}
	else
		m_visible = false;

	m_direction.x = m_m[0][0];
	m_direction.y = m_m[0][1];
	m_direction.z = m_m[0][2];
	m_direction = glm::normalize(m_direction);

	if (IsUnit())
	{

		Move();
		Rotate(glm::vec3(0.0, 10.0, 0.0) * (m_deltaTime / 1000.0f));
		SetHeight(Core::GetCore()->GetMap()->GetTerrain()->GetHeight(m_m[3][0], m_m[3][2]));
	}

	if (IsAnimated())
	{
		m_animationTime += m_deltaTime * m_animationState->animations[m_animationIndex].speed;
		long long totalAnimationTime = m_animationState->animations[m_animationIndex].animation->GetTotalTime();
		if (m_animationTime > totalAnimationTime)
		{
			m_animationTime -= totalAnimationTime;
			if (m_animationState->animations[m_animationIndex].mode != Entity::ANIMATION_MODE::LOOP)
			{
				SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
				SetAnimationState(m_entity->GetAnimationState("IDLE"));
			}
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
	{
		Scale(1.0f / state->scale);
		m_modelConditionState->model->RemoveInstance(shared_from_this());
	}
	m_modelConditionState = state;
	Scale(state->scale);
	m_modelConditionState->model->AddInstance(shared_from_this());
}

void Instance::SetAnimationState(std::shared_ptr<Entity::AnimationState> state)
{
	if (state == nullptr)
		return;
	m_animationState = state;
	m_animationIndex = 0; //std::rand() % m_animationState->animations.size();
}

std::shared_ptr<Material> Instance::GetMaterial(const std::string& meshName)
{
	const auto& it = m_modelConditionState->materials.find(meshName);
	if (it == m_modelConditionState->materials.end())
	{
		std::cout << "WARNING!: No material defined for mesh: " + meshName << std::endl;
		return nullptr;
	}
	return std::get<1>(it->second);
}