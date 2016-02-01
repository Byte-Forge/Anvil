#include "Material.hpp"
#include "../Exception.hpp"
#include <fstream>
#include <cereal/archives/json.hpp>

using namespace hpse;

void Material::Load(const std::string &path)
{
	std::ifstream is(path);
	try
	{
		cereal::JSONInputArchive archive(is);
		archive(*this);
	}
	catch (cereal::RapidJSONException& e)
	{
		std::string m = " in file: ";
		std::string msg = e.what() + m + path;
		throw HpseException(msg, __FILE__, __LINE__);
		//maybe parse the file again to show the user where exactly the error is
	}
}

template<class Archive>
void Material::serialize(Archive& archive)
{
	archive(m_maxTessellation, m_displacementFactor, m_diffuseTexture, m_normalTexture, m_specularTexture, m_displacementTexture, m_ambientOccTexture);
}
