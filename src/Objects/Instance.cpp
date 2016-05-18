/*
************************************
* Copyright (C) 2016 ByteForge
* Instance.cpp
************************************
*/

#include "Instance.hpp"
#include "../Exception.hpp"
#include "../Core.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace anvil;

Instance::Instance(std::shared_ptr<Entity> entity, glm::vec3 &position) : m_entity(entity), m_position(position)
{

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

bool Instance::Update()
{
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
	if (it != m_modelConditionState->materials.end())
		return std::get<1>(it->second);
	else
		std::cout << "WARNING!: No material defined for mesh: " + meshName << std::endl;
	return nullptr;
}
