/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.hpp
************************************
*/

#pragma once
#include <string>
#include <memory> 
#include "../Graphics/IMesh.hpp"

namespace anvil
{
	/**
	 * @class	BF3DLoader
	 *
	 * @brief	Loads our 3D model format, which is called BF3d (ByteForge3D)
	 */
	class BF3DLoader
	{
	public:

		/**
		 * @fn	static void BF3DLoader::Load(const std::string& name, const std::string& path);
		 *
		 * @brief	Loads a BF3D Model and adds it to the ResourceManager
		 *
		 * @param	name	The name of the model that should be loaded
		 * @param	path	The basepath of our model
		 */
		static void Load(const std::string& name, const std::string& path, const std::string& skl_path = "");

	private:
		static void LoadHierarchy(const std::string &name, std::ifstream &file, std::uint32_t chunkEnd);
		static void LoadAnimation(const std::string &name, std::ifstream &file, std::uint32_t chunkEnd);
		static void LoadModel(const std::string &name, std::ifstream& file, std::uint32_t chunkEnd, const std::string &skl_path);
		static std::shared_ptr<IMesh> LoadMesh(std::ifstream& file, std::uint32_t chunkEnd);
	};
}