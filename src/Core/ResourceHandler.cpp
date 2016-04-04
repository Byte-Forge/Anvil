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
#include "../Graphics/IModel.hpp"
#include "../Graphics/ITexture.hpp"
#include "../Graphics/IParticleSystem.hpp"
#include "../Graphics/Material.hpp"
#include "../Audio/SoundBuffer.hpp"
using namespace anvil;

std::shared_ptr<Entity> ResourceHandler::GetEntity(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_entitiesDir + name, path))
		{
			JsonLoader::LoadEntity(name, path);
		}
	}
	return std::dynamic_pointer_cast<Entity> (m_resources[toUpper(name)]);
}

std::shared_ptr<IParticleSystem> ResourceHandler::GetParticleSystem(const std::string & name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_particleDir + name, path))
		{
			JsonLoader::LoadParticlesystem(name, path);
		}
	}
	return std::dynamic_pointer_cast<IParticleSystem> (m_resources[toUpper(name)]);
}

std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_texturesDir + name, path))
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
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_materialsDir + name, path))
		{
			JsonLoader::LoadMaterial(name, path);
		}
	}
	return std::dynamic_pointer_cast<Material> (m_resources[toUpper(name)]);
}


std::vector<std::string> ResourceHandler::GetTerrainMaterials()
{
	std::vector<std::string> materials;
	
	std::vector<std::string> temp;
	temp = IO::ListFiles(m_materialsDir + "terrain/", "json");
	for (int i = 0; i < temp.size(); i++)
	{
		if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
		{
			materials.push_back("terrain/" + temp[i]);
		}
	}

	for (int i = 0; i < m_modDirs.size(); i++)
	{
		temp = IO::ListFiles(m_modDirs[i] + m_materialsDir + "terrain/", "json");
		for (int i = 0; i < temp.size(); i++)
		{
			if (!(std::find(materials.begin(), materials.end(), temp[i]) != materials.end()))
			{
				materials.push_back("terrain/" + temp[i]);
			}
		}
	}
	return materials;
}

std::shared_ptr<IModel> ResourceHandler::GetModel(const std::string &name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_bf3dDir + name, path))
		{
			BF3DLoader::Load(name, path);
		}
	}
	return std::dynamic_pointer_cast<IModel> (m_resources[toUpper(name)]);
}

std::shared_ptr<SoundBuffer> ResourceHandler::GetSound(const std::string& name)
{
	std::string path;
	if (m_resources.count(toUpper(name)) == 0)
	{
		if (GetFilePath(m_soundDir + name, path))
		{
			std::shared_ptr<SoundBuffer> sound = std::make_shared<SoundBuffer>();
			sound->Load(path);
			AddResource(name, sound);
		}
	}
	return std::dynamic_pointer_cast<SoundBuffer> (m_resources[toUpper(name)]);
}

void ResourceHandler::AddResource(const std::string& name, std::shared_ptr<IResource> resource)
{
	m_resources.insert({ toUpper(name), resource });
}

int ResourceHandler::GetFilePath(std::string name, std::string& path)
{
	//test if the file is in one of the mod folders, starting with the last added mod folder
	for (size_t i = m_modDirs.size(); i > 0; i--)
	{
		const auto& dir = m_modDirs[i];
		if (fileExists(dir + "/" + name))
		{
			path = dir + "/" + name;
			return 1;
		}
	}
	if (fileExists(name)) //file in engine folder
	{
		path = name;
		return 1;
	}
	else
		throw AnvilException("No such file found: " + name, __FILE__, __LINE__);
	return 0;
}
