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
	m_albedoTextureString = "textures/default.dds";

	m_normalTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_norm.dds");
	m_normalTextureString = "textures/default_norm.dds";

	m_specularTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_spec.dds");
	m_specularTextureString = "textures/default_spec.dds";

	m_displacementTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_disp.dds");
	m_displacementTextureString = "textures/default_disp.dds";

	m_ambientOccTexture = Core::GetCore()->GetResources()->GetTexture("textures/default_ao.dds");
	m_ambientOccTextureString = "textures/default_ao.dds";
}

Material::~Material()
{

}

