#pragma once
#include "../Graphics/IRenderable.hpp"
#include <vector>


namespace hpse
{
	// chunk 0x80000003
	struct Tile
	{
		std::uint16_t tex1;
		std::uint16_t tex2; // -1 for no texture
	};

	// chunk 0x80000002
	//a Terrain is the visible part of a map, e.g. the ground, buildings, trees etc.
	class Terrain : public IRenderable
	{
	public:
		std::uint32_t width;
		std::uint32_t height;
		std::vector<std::string> textures;
		std::vector<Tile> tiles; //size is width * height

		Terrain(std::uint32_t width, std::uint32_t height);
		~Terrain();
	private:
		std::uint32_t tileSize = 10;
	};
}