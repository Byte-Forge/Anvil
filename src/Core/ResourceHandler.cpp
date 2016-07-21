/*
************************************
* Copyright (C) 2016 ByteForge
* ResourceHandler.cpp
************************************
*/

#include "ResourceHandler.hpp"
#include <iostream>
#include "../Util.hpp"
#include "../Loaders/TextureLoader.hpp"
#include "../Loaders/JsonLoader.hpp"
#include "../Loaders/BF3DLoader.hpp"
#include "../Util/Platform.hpp"
#include "../Exception.hpp"
#include "../Objects/Entity.hpp"
#include "../Graphics/Hierarchy.hpp"
#include "../Graphics/Animation.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/ITexture.hpp"
#include "../Graphics/IParticleSystem.hpp"
#include "../Graphics/Material.hpp"
#include "../Audio/SoundBuffer.hpp"

using namespace anvil;

std::shared_ptr<Entity> ResourceHandler::GetEntity(const std::string &name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			JsonLoader::LoadEntity(name, path);
		}
	}
	return std::dynamic_pointer_cast<Entity> (m_resources[name]);
}

std::vector<std::string> ResourceHandler::GetEntityList()
{
	std::vector<std::string> entities;
	std::vector<std::string> temp = IO::ListFilesRecursively("entities/", "json");

	for (unsigned int i = 0; i < m_modDirs.size(); i++)
	{
		std::vector<std::string> temp2 = IO::ListFilesRecursively(m_modDirs[i] + "/entities/", "json");
		for (unsigned int i = 0; i < temp2.size(); i++)
		{
			std::cout << temp2[i] << std::endl;
			if (std::find(temp.begin(), temp.end(), temp2[i]) == temp.end())
			{
				temp.push_back(temp2[i]);
			}
		}
	}

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (temp[i].find("template") == 0)
		{
			std::cout << temp[i] << std::endl;
			entities.push_back(temp[i]);
		}
	}

	return entities;
}

std::shared_ptr<IParticleSystem> ResourceHandler::GetParticleSystem(const std::string & name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			JsonLoader::LoadParticlesystem(name, path);
		}
	}
	return std::dynamic_pointer_cast<IParticleSystem> (m_resources[name]);
}

std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			TextureLoader::LoadTexture(name, path);
		}
	}			
	return std::dynamic_pointer_cast<ITexture> (m_resources[name]);
}

std::shared_ptr<ITexture> ResourceHandler::GetTextureArray(std::vector<std::string> names)
{
	std::vector<std::string> paths;
	for (auto& name : names)
	{
		std::string path;
		if (GetFilePath(name, path))
		{
			paths.push_back(path);
		}
	}
	return TextureLoader::LoadTextureArray(paths);
}

std::shared_ptr<Material> ResourceHandler::GetMaterial(const std::string &name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			JsonLoader::LoadMaterial(name, path);
		}
	}
	return std::dynamic_pointer_cast<Material> (m_resources[name]);
}


std::vector<std::string> ResourceHandler::GetTerrainMaterials()
{
	std::vector<std::string> materials;
	
	std::vector<std::string> temp;
	temp = IO::ListFiles("materials/terrain/", "json");
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
		{
			materials.push_back("materials/terrain/" + temp[i]);
		}
	}

	for (unsigned int i = 0; i < m_modDirs.size(); i++)
	{
		temp = IO::ListFiles(m_modDirs[i] + "materials/terrain/", "json");
		for (unsigned int i = 0; i < temp.size(); i++)
		{
			if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
			{
				materials.push_back("materials/terrain/" + temp[i]);
			}
		}
	}
	return materials;
}

std::shared_ptr<IModel> ResourceHandler::GetModel(const std::string &name, const std::string &skl_path)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			BF3DLoader::Load(name, path, skl_path);
		}
	}
	return std::dynamic_pointer_cast<IModel> (m_resources[name]);
}

std::shared_ptr<Hierarchy> ResourceHandler::GetHierarchy(const std::string &name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			BF3DLoader::Load(name, path);
		}
	}
	return std::dynamic_pointer_cast<Hierarchy> (m_resources[name]);
}

std::shared_ptr<Animation> ResourceHandler::GetAnimation(const std::string &name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			BF3DLoader::Load(name, path);
		}
	}
	return std::dynamic_pointer_cast<Animation> (m_resources[name]);
}

std::shared_ptr<SoundBuffer> ResourceHandler::GetSound(const std::string& name)
{
	std::string path;
	const auto& it = m_resources.find(name);
	if (it == m_resources.end())
	{
		if (GetFilePath(name, path))
		{
			std::shared_ptr<SoundBuffer> sound = std::make_shared<SoundBuffer>();
			sound->Load(path);
			AddResource(name, sound);
		}
	}
	return std::dynamic_pointer_cast<SoundBuffer> (m_resources[name]);
}

void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
{
	m_resources_mutex.lock();
	m_resources.emplace(name,resource);
	m_resources_mutex.unlock();
}

bool ResourceHandler::GetFilePath(const std::string name, std::string& path)
{
	//test if the file is in one of the mod folders, starting with the last added mod folder
	unsigned int size = m_modDirs.size();
	for (unsigned int i = 0; i < size; i++)
	{
		const auto& dir = m_modDirs[size - i - 1];
		if (fileExists(dir + "/" + name))
		{
			path = dir + "/" + name;
			return true;
		}
	}
	if (fileExists(name)) //file in engine folder
	{
		path = name;
		return true;
	}
	else
		throw AnvilException("No such file found: " + name, __FILE__, __LINE__);
	return false;
}

void ResourceHandler::AddModDir(const std::string& dir)
{
	if (std::find(m_modDirs.begin(), m_modDirs.end(), dir) != m_modDirs.end())
		return;
	m_modDirs.push_back(dir);
}
