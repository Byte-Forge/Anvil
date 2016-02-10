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
	class TextureLoader
	{
	public:
		static void LoadTexture(const std::string& name, const std::string& path);
		static std::shared_ptr<ITexture> LoadTextureArray(std::vector<std::string> paths);
	};
}