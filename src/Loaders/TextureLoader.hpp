/*
************************************
* Copyright (C) 2016 ByteForge
* TextureLoader.hpp
************************************
*/

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Graphics/ITexture.hpp"

namespace anvil
{
	/**
	 * @class	TextureLoader
	 *
	 * @brief	A texture loader.
	 */
	class TextureLoader
	{
	public:

		/**
		 * @fn	static void TextureLoader::LoadTexture(const std::string& name, const std::string& path);
		 *
		 * @brief	Loads a texture.
		 *
		 * @param	name	The name.
		 * @param	path	Full pathname of the file.
		 */
		static void LoadTexture(const std::string& name, const std::string& path);

		/**
		 * @fn	static std::shared_ptr<ITexture> TextureLoader::LoadTextureArray(const std::vector<std::string>& paths);
		 *
		 * @brief	Loads texture array.
		 *
		 * @param	paths	The paths.
		 *
		 * @return	The texture array.
		 */
		static std::shared_ptr<ITexture> LoadTextureArray(const std::vector<std::string>& paths);
	};
}