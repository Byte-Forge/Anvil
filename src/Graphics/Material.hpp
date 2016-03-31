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
	/**
	 * @class	Material
	 *
	 * @brief	A material.
	 */
	class Material : public IResource
	{
	public:
		inline void SetDisplacementFactor(float factor) { m_displacementFactor = factor; }
		inline void SetDiffuseTexture(std::string diffuseTexture) { m_diffuseTexture = diffuseTexture; }
		inline void SetNormalTexture(std::string normalTexture) { m_normalTexture = normalTexture; }
		inline void SetSpecularTexture(std::string specularTexture) { m_specularTexture = specularTexture; }
		inline void SetDisplacementTexture(std::string displacementTexture) { m_displacementTexture = displacementTexture; }
		inline void SetAmbientOcclusionTexture(std::string ambientOccTexture) { m_ambientOccTexture = ambientOccTexture; }

		inline float GetDisplacementFactor() { return m_displacementFactor; }
		inline std::string GetDiffuseTexture() { return m_diffuseTexture; }
		inline std::string GetNormalTexture() { return m_normalTexture; }
		inline std::string GetSpecularTexture() { return m_specularTexture; }
		inline std::string GetDisplacementTexture() { return m_displacementTexture; }
		inline std::string GetAmbientOcclusionTexture() { return m_ambientOccTexture; }

	private:
		float m_displacementFactor = 0.01f; //default

		std::string m_diffuseTexture; 
		std::string m_normalTexture; 
		std::string m_specularTexture; 
		std::string m_displacementTexture; 
		std::string m_ambientOccTexture; 
	};
}