/*
************************************
* Copyright (C) 2016 ByteForge
* Material.hpp
************************************
*/

#pragma once
#include <string>
#include "../Core/IResource.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Graphics/ITexture.hpp"
#include "../Core.hpp"

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
		Material();

		~Material();

		inline void SetDisplacementFactor(float factor) { m_displacementFactor = factor; }
		inline void SetUPerSecond(float value) { m_uPerSec = value; }
		inline void SetVPerSecond(float value) { m_vPerSec = value; }
		inline void SetAlbedoTexture(std::string albedoTexture) { m_albedoTextureString = albedoTexture;  m_albedoTexture = Core::GetCore()->GetResources()->GetTexture(albedoTexture); }
		inline void SetNormalTexture(std::string normalTexture) { m_normalTextureString = normalTexture; m_normalTexture = Core::GetCore()->GetResources()->GetTexture(normalTexture); }
		inline void SetSpecularTexture(std::string specularTexture) { m_specularTextureString = specularTexture; m_specularTexture = Core::GetCore()->GetResources()->GetTexture(specularTexture); }
		inline void SetDisplacementTexture(std::string displacementTexture) { m_displacementTextureString = displacementTexture; m_displacementTexture = Core::GetCore()->GetResources()->GetTexture(displacementTexture); }
		inline void SetAmbientOcclusionTexture(std::string ambientOccTexture) { m_ambientOccTextureString = ambientOccTexture; m_ambientOccTexture = Core::GetCore()->GetResources()->GetTexture(ambientOccTexture); }

		inline float GetDisplacementFactor() { return m_displacementFactor; }
		inline float GetUPerSecond() { return m_uPerSec; }
		inline float GetVPerSecond() { return m_vPerSec; }
		inline std::shared_ptr<ITexture> GetAlbedoTexture() { return m_albedoTexture; }
		inline std::shared_ptr<ITexture> GetNormalTexture() { return m_normalTexture; }
		inline std::shared_ptr<ITexture> GetSpecularTexture() { return m_specularTexture; }
		inline std::shared_ptr<ITexture> GetDisplacementTexture() { return m_displacementTexture; }
		inline std::shared_ptr<ITexture> GetAmbientOcclusionTexture() { return m_ambientOccTexture; }

		inline std::string GetAlbedoTextureString() { return m_albedoTextureString; }
		inline std::string GetNormalTextureString() { return m_normalTextureString; }
		inline std::string GetSpecularTextureString() { return m_specularTextureString; }
		inline std::string GetDisplacementTextureString() { return m_displacementTextureString; }
		inline std::string GetAmbientOcclusionTextureString() { return m_ambientOccTextureString; }

	private:
		float m_displacementFactor = 0.01f; //default
		float m_uPerSec = 0.0f;
		float m_vPerSec = 0.0f;

		std::shared_ptr<ITexture> m_albedoTexture;
		std::string m_albedoTextureString;
		std::shared_ptr<ITexture> m_normalTexture;
		std::string m_normalTextureString;
		std::shared_ptr<ITexture> m_specularTexture;
		std::string m_specularTextureString;
		std::shared_ptr<ITexture> m_displacementTexture;
		std::string m_displacementTextureString;
		std::shared_ptr<ITexture> m_ambientOccTexture;
		std::string m_ambientOccTextureString;
	};
}