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
	std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name)
	{
		if (m_resources.count(toUpper(name)) == 0)
		{
			TextureLoader::Load(name);
		}
		if (m_resources.count(toUpper(name)) > 0)
		{
			return std::dynamic_pointer_cast<ITexture> (m_resources[toUpper(name)]);
		}
		std::cout << "ERROR: no such resource found: " << name << std::endl;
		return nullptr;
	}

	void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
	{
		m_resources.insert({ toUpper(name), resource });
	}
}

