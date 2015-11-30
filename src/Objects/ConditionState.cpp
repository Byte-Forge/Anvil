//
// Created by michael on 22.11.15.
//
#include "ConditionState.hpp"

using namespace hpse;

void ConditionState::ReplaceTexture(std::string tex, std::string replace)
{
	if (m_textureReplaces.count(tex) > 0)
		m_textureReplaces[tex] = replace;
	else
		m_textureReplaces.insert({ tex, replace });
}

void ConditionState::AddProp(std::string pivot, std::string prop)
{
	if (m_props.count(pivot) > 0)
		m_props[pivot] = prop;
	else
		m_props.insert({ pivot, prop });
}

void ConditionState::AddFX(std::string pivot, std::string fx)
{
	if (m_boneFXs.count(pivot) > 0)
		m_boneFXs[pivot] = fx;
	else
		m_boneFXs.insert({ pivot, fx });
}

void ConditionState::AddAnimation(std::string animation)
{
	m_animations.push_back(animation);
}

void ConditionState::AddSound(std::string sound)
{
	m_sounds.push_back(sound);
}