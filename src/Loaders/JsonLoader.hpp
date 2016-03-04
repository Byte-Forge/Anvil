/*
************************************
* Copyright (C) 2016 ByteForge
* JsonLoader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	/**
	 * @class	JsonLoader
	 *
	 * @brief	A JSON loader.
	 */
	class JsonLoader
	{
	public:

		/**
		 * @fn	static void JsonLoader::LoadMaterial(const std::string& name, const std::string& path);
		 *
		 * @brief	Loads a material.
		 *
		 * @param	name	The name.
		 * @param	path	Full pathname of the file.
		 */
		static void LoadMaterial(const std::string& name, const std::string& path);

		/**
		 * @fn	static void JsonLoader::LoadEntity(const std::string& name, const std::string& path);
		 *
		 * @brief	Loads an entity.
		 *
		 * @param	name	The name.
		 * @param	path	Full pathname of the file.
		 */
		static void LoadEntity(const std::string& name, const std::string& path);

		/**
		 * @fn	static void JsonLoader::LoadParticlesystem(const std::string& name, const std::string& path);
		 *
		 * @brief	Loads a particlesystem.
		 *
		 * @param	name	The name.
		 * @param	path	Full pathname of the file.
		 */
		static void LoadParticlesystem(const std::string& name, const std::string& path);
	};
}