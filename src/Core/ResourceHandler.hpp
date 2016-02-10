/*
************************************
* Copyright (C) 2016 ByteForge
* ResourceHandler.hpp
************************************
*/

#pragma once
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include "IResource.hpp"
#include "../Objects/Entity.hpp"
#include "../Types/BF3D.hpp"
#include "../Graphics/ITexture.hpp"
#include "../Graphics/Material.hpp"

namespace anvil
{
    class ResourceHandler
    {
    public:
		std::shared_ptr<Entity> GetEntity(const std::string &name);

		std::shared_ptr<ITexture> GetTexture(const std::string &name);
		std::shared_ptr<ITexture> GetTextureArray(std::vector<std::string> names);

		std::shared_ptr<Material> GetMaterial(const std::string &name);
		std::vector<std::string> GetTerrainMaterials();

		std::shared_ptr<BF3DModel> GetModel(const std::string &name);

		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

		inline void AddModDir(const std::string& dir)
		{
			//this is not working dont know why
			/*
			if (std::find(m_modDirs.begin(), m_modDirs.end(), m_modDir + dir) != m_modDirs.end())
				return;
			m_modDirs.push_back(dir);
			*/
		}

    private:
		std::string m_texturesDir = "textures/";
		std::string m_shadersDir = "shader/";
		std::string m_materialsDir = "materials/";
		std::string m_bf3dDir = "bf3d/";
		std::string m_uiDir = "ui/";
		std::string m_entitiesDir = "entities/";
		std::string m_modDir = "mods/";

		std::vector<std::string> m_modDirs;

        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
		int GetFilePath(std::string name, std::string* path);
    };
}


