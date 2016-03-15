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
	m_model = parent->m_model;
	m_model->AddEntity(this);
}

Entity::~Entity()
{
	//m_model->RemoveEntity(this);
}