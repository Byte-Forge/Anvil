/*
************************************
* Copyright (C) 2016 ByteForge
* Material.hpp
************************************
*/

#pragma once
#include <string>
#include "../Core/IResource.hpp"

namespace anvil
{
	class Material : public IResource
	{
	public:
		float m_displacementFactor = 0.01f; //default

		std::string m_diffuseTexture; //default texture
		std::string m_normalTexture; //default texture 
		std::string m_specularTexture; //default texture
		std::string m_displacementTexture; //default texture
		std::string m_ambientOccTexture; //default texture
	};
}