#pragma once
#include <string>
#include "../Core/IResource.hpp"

namespace hpse
{
	class Material : public IResource
	{
	public:
		int m_maxTessellation;
		float m_displacementFactor;

		std::string m_diffuseTexture;
		std::string m_normalTexture;
		std::string m_specularTexture;
		std::string m_displacementTexture;
		std::string m_ambientOccTexture;
	};
}