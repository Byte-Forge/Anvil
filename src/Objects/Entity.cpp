/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.cpp
************************************
*/

#include "Entity.hpp"
#include "../Core.hpp"
#include "../Graphics.hpp"
#include "Instance.hpp"
#include <cstdlib>
#include <ctime>

using namespace anvil;

Entity::Entity() 
{

}

Entity::Entity(std::shared_ptr<Entity> parent)
{
	m_health = parent->m_health;
	m_speed = parent->m_speed;
	m_modelConditionStates = parent->m_modelConditionStates;
	m_animationStates = parent->m_animationStates;
}

Entity::~Entity()
{
	
}

void Entity::Update()
{
	int size = m_instances.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_instances[i]->Update())
		{
			m_instances[i]->Unlink();
			m_instances.erase(m_instances.begin() + i);
			i--;
			size -= 1;
		}
	}
}

void Entity::AddInstance(glm::vec3 &position, glm::vec3 &euler)
{
	if (!m_resourcesLoaded)
	{
		LoadResources();
		m_resourcesLoaded = true;
	}
	if (m_instances.size() == 0)
		Core::GetCore()->GetGraphics()->GetRenderer()->RegisterEntity(shared_from_this());
	std::shared_ptr<Instance> i = std::make_shared<Instance>(shared_from_this(), position, euler);
	i->Init();
	m_instances.push_back(i);
}

std::shared_ptr<Entity::ModelConditionState> Entity::GetModelConditionState(const std::string& name)
{
	const auto& it = m_modelConditionStates.find(name);
	if (it != m_modelConditionStates.end())
		return it->second;
	else
	{
		std::cout << "WARNING!: Entity object has no ModelConditionState " + name << std::endl;
		return nullptr;
	}
}

std::shared_ptr<Entity::AnimationState> Entity::GetAnimationState(const std::string& name)
{
	const auto& it = m_animationStates.find(name);
	if (it != m_animationStates.end())
		return it->second;
	else
	{
		//std::cout << "WARNING!: Entity object has no AnimationState " + name << std::endl;
		return nullptr;
	}
}

void Entity::LoadResources()
{
	for (auto& state : m_modelConditionStates)
	{
		state.second->model = Core::GetCore()->GetResources()->GetModel(state.second->modelName, state.second->hierarchyPath);
		for (auto& mat : state.second->materials)
		{
			std::get<1>(mat.second) = Core::GetCore()->GetResources()->GetMaterial(std::get<0>(mat.second));
		}
	}
	for (auto& state : m_animationStates)
	{
		state.second->animation = Core::GetCore()->GetResources()->GetAnimation(state.second->animationName);
	}
}
