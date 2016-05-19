/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.cpp
************************************
*/

#include "Instance.hpp"
#include "../Exception.hpp"
#include "../Core.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/Material.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace anvil;

Instance::Instance(std::shared_ptr<Entity> entity, glm::vec3 &position) : m_entity(entity), m_position(position)
{
	srand(time(NULL));
}

Instance::~Instance()
{

}

void Instance::Init()
{
	SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
	//SetAnimationState(m_entity->GetAnimationState("IDLE"));
	SetHealth(m_entity->GetHealth());
}

void Instance::Unlink()
{
	if (m_model != nullptr)
		m_model->RemoveInstance(shared_from_this());
}

bool Instance::Update()
{
	//int r = rand() % 15;
	//m_health -= r;
	if (m_health <= 0)
		return false;
	return true;
}

void Instance::SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state)
{
	if (state == nullptr)
		return;
	if (m_model != nullptr)
		m_model->RemoveInstance(shared_from_this());
	m_modelConditionState = state;
	m_model = m_modelConditionState->model;
	m_model->AddInstance(shared_from_this());
}

void Instance::SetAnimationState(std::shared_ptr<Entity::AnimationState> state)
{
	if (state == nullptr)
		return;
	m_animationState = state;
}

std::shared_ptr<Material> Instance::GetMaterial(const std::string& meshName)
{
	const auto& it = m_modelConditionState->materials.find(toUpper(meshName));
	if (it == m_modelConditionState->materials.end())
	{
		std::cout << "WARNING!: No material defined for mesh: " + meshName << std::endl;
		const auto& i = m_modelConditionState->materials.begin();
		return std::get<1>(i->second);
	}
	return std::get<1>(it->second);
}
