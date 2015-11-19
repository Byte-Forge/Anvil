//
// Created by stephan on 11.11.15.
//
#include "ResourceHandler.hpp"
#include <iostream>
#include "../Loaders/Util.hpp"
#include "../Loaders/TextureLoader.hpp"
#include "../Loaders/W4DLoader.hpp"

namespace hpse
{
	static ResourceHandler* unique;

	ResourceHandler* ResourceHandler::instance()
	{
		if (unique == NULL)
			unique = new ResourceHandler();
		return unique;
	}

	std::shared_ptr<IResource> ResourceHandler::GetResource(const std::string &name, ResourceType type)
	{
		if (m_resources.count(toUpper(name)) == 0)
		{
			switch (type)
			{
			case w4d:
				W4DLoader::Load(name);
				break;
			case texture:
				TextureLoader::Load(name);
				break;
			}
		}
		if (m_resources.count(toUpper(name)) > 0)
		{
			return m_resources[toUpper(name)];
		}
		cout << "no such resource found: " << name << endl;
		return nullptr;
	}

	void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
	{
		string upper = name;
		std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
		m_resources.insert({ upper, resource });
	}
}

