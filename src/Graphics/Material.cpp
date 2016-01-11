#include "Material.hpp"
#include "../Util/tinyxml2.h"
#include "../Exception.hpp"
#include <iostream>

using namespace hpse;
using namespace tinyxml2;

void Material::Load(const std::string& path)
{
	XMLDocument doc;
	doc.LoadFile(path.c_str());

	XMLNode *material = doc.FirstChild();
	if (material == nullptr)  throw HpseException("missing material node: " + path, __FILE__, __LINE__);

	XMLElement *max_tess = material->FirstChildElement("max_tessellation");
	if (max_tess == nullptr) throw HpseException("material has no max_tessellation member: " + path, __FILE__, __LINE__);
	max_tess->QueryIntText(&m_maxTessellation);

	XMLElement *disp_factor = material->FirstChildElement("displacement_factor");
	if (disp_factor == nullptr) throw HpseException("material has no displacement_factor member: " + path, __FILE__, __LINE__);
	disp_factor->QueryFloatText(&m_displacementFactor);

	XMLElement *textures = material->FirstChildElement("textures");
	if (textures == nullptr) throw HpseException("material has no textures member: " + path, __FILE__, __LINE__);

	XMLElement *diffuse = textures->FirstChildElement("diffuse");
	if (diffuse == nullptr) throw HpseException("material has no diffuse texture member: " + path, __FILE__, __LINE__);
	m_diffuseTexture = diffuse->GetText();

	XMLElement *normal = textures->FirstChildElement("normal");
	if (normal == nullptr) m_normalTexture = "";
	m_normalTexture = normal->GetText();

	XMLElement *specular = textures->FirstChildElement("specular");
	if (specular == nullptr) m_specularTexture = "";
	m_specularTexture = specular->GetText();

	XMLElement *displacement = textures->FirstChildElement("displacement");
	if (displacement == nullptr) m_displacementTexture = "";
	m_displacementTexture = displacement->GetText();

	XMLElement *ambient_occ = textures->FirstChildElement("ambient_occ");
	if (ambient_occ == nullptr) m_ambientOccTexture = "";
	m_ambientOccTexture = ambient_occ->GetText();

	std::cout << m_diffuseTexture << std::endl;
	std::cout << m_normalTexture << std::endl;
	std::cout << m_specularTexture << std::endl;
	std::cout << m_displacementTexture << std::endl;
	std::cout << m_ambientOccTexture << std::endl;
}