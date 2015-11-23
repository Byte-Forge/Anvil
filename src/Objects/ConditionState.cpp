//
// Created by michael on 22.11.15.
//
#include "Variant.hpp"

using namespace hpse;

void Variant::SetModel(std::string model)
{
	m_model = model;
}

void Variant::AddTexReplace(std::string tex, std::string replace)
{
	m_texReplaces.insert({ tex, replace });
}

void Variant::AddAnimation(std::string name, std::string animation)
{
	m_animations.insert({ name, animation });
}