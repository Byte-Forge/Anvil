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

void TextureLoader::Load(const std::string& name)
{
	std::cout << "loading texture: " << name << std::endl;
	const std::string path = "textures/";
	const std::string ext = ".dds";

	gli::texture Texture = gli::load(path + name + ext);
	if (Texture.empty())
		throw HpseException("Failed to load empty texture" + path + name + ext, __FILE__, __LINE__);

	auto tex = Core::GetGraphics()->GetTexture();
	if(!tex->Load(Texture))
		throw HpseException("Failed to load texture" + path + name + ext, __FILE__, __LINE__);

	Core::GetResources()->AddResource(name, tex);
}
