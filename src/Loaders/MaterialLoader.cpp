#include "MaterialLoader.hpp"
#include "../Graphics/Material.hpp"
#include "../Core.hpp"
#include "../Loaders/Util.hpp"
#include "../Exception.hpp"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace hpse;
using namespace rapidjson;

void MaterialLoader::LoadMaterial(const std::string &name, const std::string &path)
{
	std::shared_ptr<Material> mat = std::make_shared<Material>();

	FILE* f = fopen(path.c_str(), "r");
	char readBuffer[65536];
	FileReadStream fs(f, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(fs);

	if (d["material"].IsObject())
	{
		if (d["material"]["displacement_factor"].IsDouble())
			mat->m_displacementFactor = d["material"]["displacement_factor"].GetDouble();
		if (d["material"]["diffuse"].IsString())
			mat->m_diffuseTexture = d["material"]["diffuse"].GetString();
		if (d["material"]["normal"].IsString())
			mat->m_normalTexture = d["material"]["normal"].GetString();
		if (d["material"]["specular"].IsString())
			mat->m_specularTexture= d["material"]["specular"].GetString();
		if (d["material"]["displacement"].IsString())
			mat->m_displacementTexture = d["material"]["displacement"].GetString();
		if (d["material"]["ambient_occ"].IsString())
			mat->m_ambientOccTexture = d["material"]["ambient_occ"].GetString();
	}
	else
	{
		throw HpseException("Material file has no material object", __FILE__, __LINE__);
	}

	fclose(f);

	Core::GetCore()->GetResources()->AddResource(toUpper(name), mat);
}
