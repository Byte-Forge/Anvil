//
// Created by stephan on 11.11.15.
//
#include "ResourceHandler.hpp"
#include <iostream>
#include "../Loaders/Util.hpp"
#include "../Loaders/EntityLoader.hpp"
#include "../Loaders/TextureLoader.hpp"
#include "../Loaders/MaterialLoader.hpp"
#include "../Loaders/W4DLoader.hpp"
#include "../Util/Platform.hpp"
#include "../Exception.hpp"

using namespace hpse;

std::shared_ptr<Entity> ResourceHandler::GetEntity(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_objectsDir + name, &path))
		{
			EntityLoader::LoadEntity(name, path);
		}
	}
	return std::dynamic_pointer_cast<Entity> (m_resources[toUpper(name)]);
}

std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_texturesDir + name, &path))
		{
			TextureLoader::LoadTexture(name, path);
		}
	}			
	return std::dynamic_pointer_cast<ITexture> (m_resources[toUpper(name)]);
}

std::shared_ptr<ITexture> ResourceHandler::GetTextureArray(std::vector<std::string> names)
{
	std::vector<std::string> paths;
	for (auto& name : names)
	{
		std::string path;
		name = m_texturesDir + name;
		if (GetFilePath(name, &path))
		{
			paths.push_back(path);
		}
	}
	return TextureLoader::LoadTextureArray(paths);
}

std::shared_ptr<Material> ResourceHandler::GetMaterial(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_materialsDir + name, &path))
		{
			MaterialLoader::LoadMaterial(name, path);
		}
	}
	return std::dynamic_pointer_cast<Material> (m_resources[toUpper(name)]);
}


std::vector<std::string> ResourceHandler::GetTerrainMaterials()
{
	std::vector<std::string> materials;
	
	std::vector<std::string> temp;
	temp = IO::ListFiles(m_materialsDir + "terrain/", "xml");
	for (int i = 0; i < temp.size(); i++)
	{
		if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
		{
			materials.push_back(temp[i]);
		}
	}

	for (int i = 0; i < m_modDirs.size(); i++)
	{
		temp = IO::ListFiles(m_modDirs[i] + "/terrain/", "xml");
		for (int i = 0; i < temp.size(); i++)
		{
			if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
			{
				materials.push_back(temp[i]);
			}
		}
	}
	return materials;
}

std::shared_ptr<W4DModel> ResourceHandler::GetModel(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_w4dDir + name, &path))
		{
			W4DLoader::Load(name, path);
		}
	}
	return std::dynamic_pointer_cast<W4DModel> (m_resources[toUpper(name)]);
}


void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
{
	m_resources.insert({ toUpper(name), resource });
}

int ResourceHandler::GetFilePath(std::string name, std::string* path)
{
	//test if the file is in one of the mod folders, starting with the last added mod folder
	for (int i = m_modDirs.size(); i > 0; i--)
	{
		const auto& dir = m_modDirs[i];
		if (fileExists(dir + "/" + name))
		{
			*path = dir + "/" + name;
			return 1;
		}
	}
	if (fileExists(name)) //file in engine folder
	{
		*path = name;
		return 1;
	}
	throw HpseException("No such file found: " + name, __FILE__, __LINE__);
	return 0;
}
