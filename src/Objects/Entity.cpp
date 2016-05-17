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
	SetModel(parent->m_model_string); //old

	m_modelConditionStates = parent->m_modelConditionStates;
	m_animationStates = parent->m_animationStates;
}

Entity::~Entity()
{
	if (m_model != nullptr)		//old
		m_model->RemoveEntity(this);	//old
}

void Entity::Update()
{
	/*
	int size = m_instances.size();
	for (int i = 0; i < size; i++)
	{
		if (!m_instances[i]->Update())
		{
			m_instances.erase(m_instances.begin() + i);
			i--;
			size -= 1;
		}
	}
	*/
	m_model->GetHierarchy()->Update(); //old
}

void Entity::Render(IShader &shader)
{
	for (auto& i : m_instances)
		i->Render(shader, i);
}

void Entity::SetModel(const std::string model)
{
	if (m_model != nullptr)
	{
		m_model->RemoveEntity(this);
		m_model = nullptr;
	}
	m_model_string = model;
}

void Entity::AddInstance(std::shared_ptr<Entity> entity, glm::vec3 &position)
{
	if (!m_resourcesLoaded)
	{
		LoadResources();
		m_resourcesLoaded = true;
	}
	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterEntity(entity);
	std::shared_ptr<Instance> i = std::make_shared<Instance>(entity, position);
	m_instances.push_back(i);
}


//old
void Entity::AddInstance(glm::vec3 position) 
{
	if (m_instances_old.size() == 0)
	{
		m_model = Core::GetCore()->GetResources()->GetModel(m_model_string, m_skl_path);
		m_model->AddEntity(this);
	}
	std::shared_ptr<InstanceStruct> i = std::make_shared<InstanceStruct>();

	i->health = m_health;
	i->position = position;

	m_instances_old.push_back(i);
}

std::shared_ptr<Entity::ModelConditionState> Entity::GetModelConditionState(const std::string& name)
{
	const auto& it = m_modelConditionStates.find(toUpper(name));
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
	const auto& it = m_animationStates.find(toUpper(name));
	if (it != m_animationStates.end())
		return it->second;
	else
	{
		std::cout << "WARNING!: Entity object has no AnimationState " + name << std::endl;
		return nullptr;
	}
}

std::shared_ptr<Material> Entity::GetMaterial(std::string meshName)
{
	if (m_materials.count(toUpper(meshName)) > 0)
		return m_materials[toUpper(meshName)];
}

std::deque<std::shared_ptr<Entity::InstanceStruct>> Entity::GetInstances()
{
	return m_instances_old;
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
}
