//
// Created by michael on 22.11.15.
//
#include "Variant.hpp"

using namespace hpse;

void Variant::SetModel(std::string model)
{
	m_model = model;
}

void Variant::ReplaceTexture(std::string tex, std::string replace)
{
	m_texReplaces.insert({ tex, replace });
}

void Variant::AddProp(std::string pivot, std::string prop)
{
	m_props.insert({ pivot, prop });
}

void Variant::AddConditionState(States state, ConditionState cState)
{
	m_condition_states.insert({ state, cState });
}