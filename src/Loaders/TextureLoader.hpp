#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../Graphics/ITexture.hpp"

namespace hpse
{
	class TextureLoader
	{
	public:
		static void LoadTexture(const std::string& name);
		static std::shared_ptr<ITexture> LoadTextureArray(std::vector<std::string> names);
	};
}