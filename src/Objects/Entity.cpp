//
// Created by michael on 23.11.15.
//
#include "Entity.hpp"
#include "../Core.hpp"
#include "../Exception.hpp"
#include "../Util/tinyxml2.h"

using namespace hpse;
using namespace tinyxml2;

Entity::Entity()
{

}

Entity::~Entity()
{

}

void Entity::Update()
{

}

void Entity::Render(int mode)
{

}

bool Entity::Load(const std::string& path)
{
	XMLDocument doc;
	doc.LoadFile(path.c_str());

	XMLNode *entity = doc.FirstChild();
	if (entity == nullptr)  throw HpseException("missing entity node: " + path, __FILE__, __LINE__);

	XMLElement *mesh = entity->FirstChildElement("mesh");
	if (mesh == nullptr) throw HpseException("entity has no mesh member: " + path, __FILE__, __LINE__);
	m_model= Core::GetCore()->GetResources()->GetModel(mesh->GetText());  

	XMLElement *materials = entity->FirstChildElement("materials");
	if (materials == nullptr) throw HpseException("entity has no materials member: " + path, __FILE__, __LINE__);

	for (XMLElement* material = materials->FirstChildElement(); material != NULL; material = material->NextSiblingElement())
	{
		m_materials.push_back(Core::GetCore()->GetResources()->GetMaterial(material->GetText()));
	}
	return true;
}
