/*
************************************
* Copyright (C) 2016 ByteForge
* TextureLoader.cpp
************************************
*/

#include "TextureLoader.hpp"
#include <iostream>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <gli/load.hpp>
#include "../Graphics.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Core.hpp"
#include "../Exception.hpp"
#include "../Loaders/Util.hpp"

using namespace anvil;

void TextureLoader::LoadTexture(const std::string& name, const std::string& path)
{
	gli::texture Texture = gli::load(path);
	if (Texture.empty())
		throw AnvilException("Failed to load empty texture" + path, __FILE__, __LINE__);

	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(Texture))
		throw AnvilException("Failed to load texture" + path, __FILE__, __LINE__);

	Core::GetCore()->GetResources()->AddResource(toUpper(name), tex);
}

std::shared_ptr<ITexture> TextureLoader::LoadTextureArray(std::vector<std::string> paths)
{
	std::vector<gli::texture> textures;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		gli::texture Texture = gli::load(paths[i]);
		if (Texture.empty())
			throw AnvilException("Failed to load empty texture" + paths[i], __FILE__, __LINE__);
		textures.push_back(Texture);
	}
	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(textures))
		throw AnvilException("Failed to load texture array", __FILE__, __LINE__);
	return tex;
}
