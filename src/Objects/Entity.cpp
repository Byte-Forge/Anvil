/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.cpp
************************************
*/

#include "Entity.hpp"
#include "../Core.hpp"
#include <cstdlib>
#include <ctime>

using namespace anvil;

Entity::Entity() 
{

}

Entity::Entity(std::shared_ptr<Entity> parent)
{
	SetModel(parent->m_model_string);
}

Entity::~Entity()
{
	if (m_model != nullptr)
		m_model->RemoveEntity(this);
}

void Entity::Update()
{
	std::srand(std::time(0));
	int count = m_instances.size();

	//is done this way because erase() does not work with iterators
	for (int i = 0; i < count; )
	{
		//m_instances[i]->health -= 1;
		float x = (std::rand() % 10 - 5) / 10.0;
		float y = (std::rand() % 10 - 5) / 10.0;
		m_instances[i]->position += glm::vec3(x, 0.0, y);

		if (m_instances[i]->position.x > 400 
			|| m_instances[i]->position.z > 400
			|| m_instances[i]->position.x < 0
			|| m_instances[i]->position.z < 0)
		{
			m_instances.erase(m_instances.begin() + i);
			count--;
		}
		else
			i++;
	}
}

void Entity::SetModel(std::string model)
{
	if (m_model != nullptr)
	{
		m_model->RemoveEntity(this);
		m_model = nullptr;
	}
	m_model_string = model;
}

void Entity::AddInstance(glm::vec3 position) 
{
	if (m_instances.size() == 0)
	{
		m_model = Core::GetCore()->GetResources()->GetModel(m_model_string);
		m_model->AddEntity(this);
	}
	std::shared_ptr<Instance> i = std::make_shared<Instance>();

	i->health = m_health;
	i->position = position;

	m_instances.push_back(i);
}

std::deque<std::shared_ptr<Entity::Instance>> Entity::GetInstances()
{
	return m_instances;
}