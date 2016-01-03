#include "TextureLoader.hpp"

#include <iostream>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <gli/load.hpp>
#include "../Graphics.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Core.hpp"
#include "../Exception.hpp"
using namespace hpse;


void TextureLoader::LoadTexture(const std::string& path)
{
	std::cout << "loading texture: " << path << std::endl;

	gli::texture Texture = gli::load(path);
	if (Texture.empty())
		throw HpseException("Failed to load empty texture" + path, __FILE__, __LINE__);

	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(Texture))
		throw HpseException("Failed to load texture" + path, __FILE__, __LINE__);

	Core::GetCore()->GetResources()->AddResource(path, tex);
}

std::shared_ptr<ITexture> TextureLoader::LoadTextureArray(std::vector<std::string> names)
{
	std::vector<gli::texture> textures;
	for (unsigned int i = 0; i < names.size(); i++)
	{
		std::cout << "loading texture: " << names[i] << std::endl;
		gli::texture Texture = gli::load(names[i]);
		if (Texture.empty())
			throw HpseException("Failed to load empty texture" + names[i], __FILE__, __LINE__);
		textures.push_back(Texture);
	}
	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(textures))
		throw HpseException("Failed to load texture array", __FILE__, __LINE__);
	return tex;
}
