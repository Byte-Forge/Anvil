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
	SetModelConditionState(m_entity->GetModelConditionState("DEFAULT"));
	//SetAnimationState(m_entity->GetAnimationState("IDLE"));
	SetHealth(m_entity->GetHealth());
}

Instance::~Instance()
{

}

void Instance::Render(IShader& shader, std::shared_ptr<Instance> i)
{
	m_modelConditionState->model->Render(shader, i);
}

bool Instance::Update()
{
	m_modelConditionState->model->GetHierarchy()->Update();

	return true;
}

void Instance::SetModelConditionState(std::shared_ptr<Entity::ModelConditionState> state)
{
	if (state == nullptr)
		return;
	m_modelConditionState = state;
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
