//
// Created by michael on 23.11.15.
//
#include "IEntity.hpp"
#include "../Core.hpp"
#include "../Core/ResourceHandler.hpp"
#include <iostream>

using namespace hpse;

IEntity::IEntity(std::string name)
{
	m_name = name;
}

IEntity::~IEntity()
{

}

void IEntity::SetModel(std::string model)
{
	m_w4dModel = model;
}

std::shared_ptr<IResource> IEntity::GetModel()
{
	return Core::GetResources()->GetResource(m_w4dModel, ResourceType::entity);
}

void IEntity::SetWeaponLaunchBone(std::string bone)
{
	m_weaponLaunchBone = bone;
}

void IEntity::AddProp(std::string pivot, std::string prop)
{
	if (m_props.count(pivot) > 0)
		m_props[pivot] = prop;
	else
		m_props.insert({ pivot, prop });
}

void IEntity::AddFX(std::string pivot, std::string fx)
{
	if (m_boneFXs.count(pivot) > 0)
		m_boneFXs[pivot] = fx;
	else
		m_boneFXs.insert({ pivot, fx });
}

void IEntity::AddVariant(Variant var)
{
	m_variants.push_back(var);
}

void IEntity::AddConditionState(State s, ConditionState state)
{
	if (m_conditionStates.count(s) > 0)
		std::cout << s << " is already defined!!" << std::endl;
	else
		m_conditionStates.insert({ s, state });
}