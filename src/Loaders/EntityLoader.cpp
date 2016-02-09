#include "EntityLoader.hpp"
#include "../Core.hpp"
#include "../Objects/Entity.hpp"
#include "../Loaders/Util.hpp"
#include "../Exception.hpp"
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace hpse;
using namespace rapidjson;

void EntityLoader::LoadEntity(const std::string &name, const std::string &path)
{
	std::shared_ptr<Entity> ent; 

	std::ifstream fin(path, std::ios::in);
	
	if (fin.fail())
	{
		throw HpseException("Failed to open entity: " + name, __FILE__, __LINE__);
	}

	IStreamWrapper isw(fin);
	Document d;
	d.ParseStream(isw);

	if (d["entity"].IsObject())
	{
		if (!d["entity"]["parent"].IsNull())
			ent = std::make_shared<Entity>(Core::GetCore()->GetResources()->GetEntity(d["entity"]["parent"].GetString()));
		else
			ent = std::make_shared<Entity>();

		if (!d["entity"]["model"].IsNull())
			ent->m_model = Core::GetCore()->GetResources()->GetModel(d["entity"]["model"].GetString());

		if (!d["entity"]["materials"].IsNull() && d["entity"]["materials"].IsArray())
		{
			for (int i = 0; i < d["entity"]["materials"].Size(); i++)
			{
				ent->m_materials.push_back(Core::GetCore()->GetResources()->GetMaterial(d["entity"]["materials"][i].GetString()));
			}
		}
	}
	else
	{
		throw HpseException("Entity file has no entity object: " + path, __FILE__, __LINE__);
	}

	fin.close();
	Core::GetCore()->GetResources()->AddResource(toUpper(name), ent);
}