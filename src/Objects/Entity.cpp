/*
************************************
* Copyright (C) 2016 ByteForge
* Entity.cpp
************************************
*/

#include "Entity.hpp"

using namespace anvil;

Entity::Entity()
{

}

Entity::Entity(std::shared_ptr<Entity> parent)
{
	m_model = parent->m_model;
}

Entity::~Entity()
{

}

void Entity::Update()
{

}

void Entity::Render(int mode)
{

}