/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.cpp
************************************
*/

#include "Entity.hpp"
#include "../Core.hpp"

using namespace anvil;

Entity::Entity() 
{

}

Entity::Entity(std::shared_ptr<Entity> parent)
{
	SetModel(parent->m_model);
}

Entity::~Entity()
{
	m_model->RemoveEntity(this);
}

void Entity::Update()
{

}

void Entity::SetModel(std::shared_ptr<IModel> model)
{
	if (m_model != nullptr)
		m_model->RemoveEntity(this);
	m_model = model;
	m_model->AddEntity(this);
}

void Entity::AddInstance(glm::vec3 position)
{
	Instance* i = new Instance();
	i->position = glm::vec4(position, 1.0);
	m_instances.push_back(*i);
}

std::vector<Entity::Instance> Entity::GetInstances()
{
	return m_instances;
}