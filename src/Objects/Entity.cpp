//
// Created by michael on 23.11.15.
//
#include "Entity.hpp"
#include "../Core.hpp"
#include "../Core/ResourceHandler.hpp"
#include <iostream>

using namespace hpse;

Entity::Entity(std::string name)
{
	m_name = name;
}

Entity::~Entity()
{

}

void Entity::SetModel(std::string model)
{
	m_w4dModel = model;
}

std::shared_ptr<IResource> Entity::GetModel()
{
	return Core::GetResources()->GetResource(m_w4dModel, ResourceType::entity);
}

void Entity::SetWeaponLaunchBone(std::string bone)
{
	m_weaponLaunchBone = bone;
}

void Entity::AddProp(std::string pivot, std::string prop)
{
	if (m_props.count(pivot) > 0)
		m_props[pivot] = prop;
	else
		m_props.insert({ pivot, prop });
}

void Entity::AddFX(std::string pivot, std::string fx)
{
	if (m_boneFXs.count(pivot) > 0)
		m_boneFXs[pivot] = fx;
	else
		m_boneFXs.insert({ pivot, fx });
}