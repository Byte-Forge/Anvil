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

std::string TextureLoader::m_path = "textures/";
std::string TextureLoader::m_ext = ".dds";

void TextureLoader::LoadTexture(const std::string& name)
{
	std::cout << "loading texture: " << name << std::endl;

	gli::texture Texture = gli::load(m_path + name + m_ext);
	if (Texture.empty())
		throw HpseException("Failed to load empty texture" + m_path + name + m_ext, __FILE__, __LINE__);

	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(Texture))
		throw HpseException("Failed to load texture" + m_path + name + m_ext, __FILE__, __LINE__);

	Core::GetCore()->GetResources()->AddResource(name, tex);
}

std::shared_ptr<ITexture> TextureLoader::LoadTextureArray(std::vector<std::string> names)
{
	std::vector<gli::texture> textures;
	for (int i = 0; i < names.size(); i++)
	{
		std::cout << "loading texture: " << names[i] << std::endl;
		gli::texture Texture = gli::load(m_path + names[i] + m_ext);
		if (Texture.empty())
			throw HpseException("Failed to load empty texture" + m_path + names[i] + m_ext, __FILE__, __LINE__);
		textures.push_back(Texture);
	}
	auto tex = Core::GetCore()->GetGraphics()->GetTexture();
	if (!tex->Load(textures))
		throw HpseException("Failed to load texture array", __FILE__, __LINE__);
	return tex;
}
