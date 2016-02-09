//
// Created by michael on 23.11.15.
//
#include "Entity.hpp"

using namespace hpse;

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