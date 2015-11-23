//
// Created by michael on 22.11.15.
//
#include "ConditionState.hpp"

using namespace hpse;

void ConditionState::SetModel(std::string model)
{
	m_model = model;
}

void ConditionState::ReplaceTexture(std::string tex, std::string replace)
{
	m_texReplaces.insert({ tex, replace });
}

void ConditionState::AddAnimation(std::string animation)
{
	m_animations.push_back(animation);
}

void ConditionState::AddSound(std::string sound)
{
	m_sounds.push_back(sound);
}

void ConditionState::AddProp(std::string pivot, std::string prop) 
{
	m_props.insert({ pivot, prop });
}

void ConditionState::HideProp(std::string prop)
{
	m_hide_props.push_back(prop);
}