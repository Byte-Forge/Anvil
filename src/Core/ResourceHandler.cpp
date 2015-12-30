//
// Created by stephan on 11.11.15.
//
#include "ResourceHandler.hpp"
#include <iostream>
#include "../Loaders/Util.hpp"
#include "../Loaders/TextureLoader.hpp"
#include "../Loaders/W4DLoader.hpp"
#include "../Exception.hpp"

namespace hpse
{
	std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name)
	{
		
		if (m_resources[toUpper(name)] == nullptr)
		{
			std::string path;
			for (const auto& dir : m_texDirs)
			{
				if (fileExists(dir + "/" + name))
				{
					path = dir + "/" + name;
					break;
				}
			}

			if (path.size() == 0)
			{
				throw HpseException("Could not find texture resource named " + name, __FILE__, __LINE__);
			}
			TextureLoader::LoadTexture(path);
		}			
		else
			return std::dynamic_pointer_cast<ITexture> (m_resources[toUpper(name)]);

		return nullptr;
	}

	std::shared_ptr<ITexture> ResourceHandler::GetTextureArray(std::vector<std::string> names)
	{
		std::vector<std::string> paths;
		for (const auto& name : names)
		{
			std::string path;
			for (const auto& dir : m_texDirs)
			{
				if (fileExists(dir + "/" + name))
				{
					path = dir + "/" + name;
					break;
				}
			}
			if (path.size() == 0)
			{
				throw HpseException("Could not find texture resource array", __FILE__, __LINE__);
			}
			paths.push_back(path);
		}
		

		return TextureLoader::LoadTextureArray(paths);
	}

	void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
	{
		m_resources.insert({ toUpper(name), resource });
	}
}

