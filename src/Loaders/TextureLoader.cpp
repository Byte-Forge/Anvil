#include "TextureLoader.hpp"

#include <iostream>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <gli/load.hpp>
#include "../Graphics.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Core.hpp"

using namespace hpse;

void TextureLoader::Load(const std::string& name)
{
	std::cout << "loading texture: " << name << std::endl;
	const std::string path = "textures/";
	const std::string ext = ".ktx";

	gli::texture Texture = gli::load(path + name + ext);
	if (Texture.empty())
	{
		std::cout << "Empty texture" << std::endl;
		return;
	}

	auto tex = Core::GetGraphics()->GetTexture();
	if(!tex->Load(Texture))
	{
		std::cout << "Loading failed" << std::endl;
		return;
	}

	std::shared_ptr<ITexture> p(tex.get());
	Core::GetResources()->AddResource(name, p);
}
