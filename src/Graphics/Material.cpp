/*
************************************
* Copyright (C) 2016 ByteForge
* Material.cpp
************************************
*/

#include "Material.hpp"

using namespace anvil;

Material::Material()
{
	m_albedoTexture = Core::GetCore()->GetResources()->GetTexture("textures/default.dds");
	m_normalTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_norm.dds");
	m_specularTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_norm.dds");
	m_displacementTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_disp.dds");
	m_ambientOccTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_disp.dds");
}

Material::~Material()
{

}

