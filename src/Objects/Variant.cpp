//
// Created by michael on 22.11.15.
//
#include "Variant.hpp"

using namespace hpse;

Variant::Variant(std::map<std::string, std::string> props)
{
	m_props = props;
}

Variant::~Variant()
{

}

void Variant::ReplaceTexture(std::string tex, std::string replace)
{
	if (m_textureReplaces.count(tex) > 0)
		m_textureReplaces[tex] = replace;
	else
		m_textureReplaces.insert({ tex, replace });
}

void Variant::AddProp(std::string pivot, std::string prop)
{
	if (m_props.count(pivot) > 0)
		m_props[pivot] = prop;
	else
		m_props.insert({ pivot, prop });
}
