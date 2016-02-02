#include "Material.hpp"
#include "../Exception.hpp"
#include <fstream>
#include <iostream>
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
	catch (cereal::Exception e)
	{
		//throw HpseException(path, __FILE__, __LINE__);
	}
	

	std::cout << "####: " << m_normalTexture << std::endl;
}

template<class Archive>
void Material::serialize(Archive& archive)
{
	archive(cereal::make_nvp("max_tessellation" ,m_maxTessellation), 
		cereal::make_nvp("displacement_factor", m_displacementFactor), 
		cereal::make_nvp("diffuse", m_diffuseTexture),
		cereal::make_nvp("normal", m_normalTexture),
		cereal::make_nvp("specular", m_specularTexture),
		cereal::make_nvp("displacement", m_displacementTexture),
		cereal::make_nvp("ambient_occ", m_ambientOccTexture));
}
