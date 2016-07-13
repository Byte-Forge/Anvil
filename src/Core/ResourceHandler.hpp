/*
************************************
* Copyright (C) 2016 ByteForge
* ResourceHandler.hpp
************************************
*/

#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>
#include "IResource.hpp"

namespace anvil
{
	class Entity;
	class Hierarchy;
	class Animation;
	class IParticleSystem;
	class ITexture;
	class Material;
	class IModel;
	class SoundBuffer;

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
		* @fn	std::vector<std::string> ResourceHandler::GetEntityList();
		*
		* @brief	Gets all entities.
		*
		* @return	The entitys.
		*/
		std::vector<std::string> GetEntityList();

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
		std::shared_ptr<IModel> GetModel(const std::string &name, const std::string &skl_path = "");


		/**
		* @fn	std::shared_ptr<Hierarchy> ResourceHandler::GetHierarchy(const std::string &name);
		*
		* @brief	Gets a hierarchy.
		*
		* @param	name	The name.
		*
		* @return	The hierarchy.
		*/
		std::shared_ptr<Hierarchy> GetHierarchy(const std::string &name);

		/**
		* @fn	std::shared_ptr<Animation> ResourceHandler::GetAnimation(const std::string &name);
		*
		* @brief	Gets a animation.
		*
		* @param	name	The name.
		*
		* @return	The animation.
		*/
		std::shared_ptr<Animation> GetAnimation(const std::string &name);

		/**
		* @fn	std::shared_ptr<SoundBuffer> ResourceHandler::GetSound(const std::string &name);
		*
		* @brief	Gets a sound.
		*
		* @param	name	The name.
		*
		* @return	The sound.
		*/
		std::shared_ptr<SoundBuffer> GetSound(const std::string &name);
		
		/**
		 * @fn	void ResourceHandler::AddResource(const std::string &name, std::shared_ptr<IResource> resource);
		 *
		 * @brief	Adds a resource to 'resource'.
		 *
		 * @param	name		The name.
		 * @param	resource	The resource.
		 */
		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

		void AddModDir(const std::string& dir);

    private:
		std::vector<std::string> m_modDirs;

        std::unordered_map<std::string, std::shared_ptr<IResource>> m_resources;
		std::mutex m_resources_mutex;

	private:
		bool GetFilePath(const std::string name, std::string& path);
    };
}


