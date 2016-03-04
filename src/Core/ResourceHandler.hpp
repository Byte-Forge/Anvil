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
#include "../Graphics/IModel.hpp"
#include "../Graphics/ITexture.hpp"
#include "../Graphics/IParticleSystem.hpp"
#include "../Graphics/Material.hpp"

namespace anvil
{
    /**
     * @class	ResourceHandler
     *
     * @brief	A resource handler.
     */
    class ResourceHandler
    {
    public:

		/**
		 * @fn	std::shared_ptr<Entity> ResourceHandler::GetEntity(const std::string &name);
		 *
		 * @brief	Gets an entity.
		 *
		 * @param	name	The name.
		 *
		 * @return	The entity.
		 */
		std::shared_ptr<Entity> GetEntity(const std::string &name);

		/**
		 * @fn	std::shared_ptr<IParticleSystem> ResourceHandler::GetParticleSystem(const std::string &name);
		 *
		 * @brief	Gets particle system.
		 *
		 * @param	name	The name.
		 *
		 * @return	The particle system.
		 */
		std::shared_ptr<IParticleSystem> GetParticleSystem(const std::string &name);

		/**
		 * @fn	std::shared_ptr<ITexture> ResourceHandler::GetTexture(const std::string &name);
		 *
		 * @brief	Gets a texture.
		 *
		 * @param	name	The name.
		 *
		 * @return	The texture.
		 */
		std::shared_ptr<ITexture> GetTexture(const std::string &name);

		/**
		 * @fn	std::shared_ptr<ITexture> ResourceHandler::GetTextureArray(std::vector<std::string> names);
		 *
		 * @brief	Gets texture array.
		 *
		 * @param	names	The names.
		 *
		 * @return	The texture array.
		 */
		std::shared_ptr<ITexture> GetTextureArray(std::vector<std::string> names);

		/**
		 * @fn	std::shared_ptr<Material> ResourceHandler::GetMaterial(const std::string &name);
		 *
		 * @brief	Gets a material.
		 *
		 * @param	name	The name.
		 *
		 * @return	The material.
		 */
		std::shared_ptr<Material> GetMaterial(const std::string &name);

		/**
		 * @fn	std::vector<std::string> ResourceHandler::GetTerrainMaterials();
		 *
		 * @brief	Gets terrain materials.
		 *
		 * @return	The terrain materials.
		 */
		std::vector<std::string> GetTerrainMaterials();

		/**
		 * @fn	std::shared_ptr<IModel> ResourceHandler::GetModel(const std::string &name);
		 *
		 * @brief	Gets a model.
		 *
		 * @param	name	The name.
		 *
		 * @return	The model.
		 */
		std::shared_ptr<IModel> GetModel(const std::string &name);

		/**
		 * @fn	void ResourceHandler::AddResource(const std::string &name, std::shared_ptr<IResource> resource);
		 *
		 * @brief	Adds a resource to 'resource'.
		 *
		 * @param	name		The name.
		 * @param	resource	The resource.
		 */
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
		int GetFilePath(std::string name, std::string* path);

    private:
		std::string m_texturesDir = "textures/";
		std::string m_shadersDir = "shader/";
		std::string m_materialsDir = "materials/";
		std::string m_bf3dDir = "bf3d/";
		std::string m_uiDir = "ui/";
		std::string m_entitiesDir = "entities/";
		std::string m_particleDir = "particle/";
		std::string m_modDir = "mods/";

		std::vector<std::string> m_modDirs;

        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
    };
}


