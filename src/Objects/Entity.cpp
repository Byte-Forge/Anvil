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
#include "glm/gtx/rotate_vector.hpp"
#include <cstdlib>
#include <ctime>

using namespace anvil;

Entity::Entity(std::string name) : m_name(name)
{
	//m_properties = Properties();
}

Entity::Entity(std::string name, std::shared_ptr<Entity> parent) : m_name(name)
{
	m_properties = parent->GetProperties();
	m_modelConditionStates = parent->m_modelConditionStates;
	m_animationStates = parent->m_animationStates;
}			

Entity::~Entity()
{
	
}

void Entity::Update()
{

}

std::shared_ptr<Instance> Entity::AddInstance(const glm::vec3 &position, const glm::vec3 &euler)
{
	if (!m_resourcesLoaded)
	{
		LoadResources();
		m_resourcesLoaded = true;
	}
	std::shared_ptr<Instance> i = std::make_shared<Instance>(shared_from_this(), position, euler);
	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterInstance(i);

	for (Child c : m_children)
	{
		std::shared_ptr<Entity> e = Core::GetCore()->GetResources()->GetEntity(c.name);
		c.position = glm::rotateX(c.position, glm::radians(euler.x));
		c.position = glm::rotateY(c.position, glm::radians(euler.y));
		c.position = glm::rotateZ(c.position, glm::radians(euler.z));
		e->AddInstance(position + c.position, c.rotation + euler);
	}
	return i;
}

std::shared_ptr<Entity::ModelConditionState> Entity::GetModelConditionState(const std::string& name)
{
	const auto& it = m_modelConditionStates.find(name);
	if (it != m_modelConditionStates.end())
		return it->second;
	else
	{
		std::cout << "WARNING!: Entity object " + m_name + " has no ModelConditionState " + name << std::endl;
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
		//std::cout << "WARNING!: Entity object " + m_name + "  has no AnimationState " + name << std::endl;
		return nullptr;
	}
}

void Entity::LoadResources()
{
	for (auto& state : m_modelConditionStates)
	{
		state.second->properties.model = Core::GetCore()->GetResources()->GetModel(state.second->properties.modelName, state.second->properties.hierarchyPath);
		for (auto& mat : state.second->properties.materials)
		{
			std::get<1>(mat.second) = Core::GetCore()->GetResources()->GetMaterial(std::get<0>(mat.second));
		}
	}
	for (auto& state : m_animationStates)
	{
		for (auto& ani : state.second->animations)
			ani.animation = Core::GetCore()->GetResources()->GetAnimation(ani.animationName);
	}
}
