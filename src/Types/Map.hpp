#pragma once
#include <stdint.h>
#include <string>
#include <vector>

namespace hpse
{
	////////////////////////////////////////////
	//MAP
	////////////////////////////////////////////

	// chunk 0x80000003
	struct Tile
	{
		std::uint16_t tex1;
		std::uint16_t tex2; // -1 for no texture
	};

	// chunk 0x80000002
	struct HeightMap
	{
		//size is width * height
		std::int32_t vertexHeights[1];
	};

	// chunk 0x80000001
	struct MapHeader 
	{
		std::uint32_t width;
		std::uint32_t height;
		std::uint8_t playerCount;
		std::string textures[1];
	};

	// chunk 0x80000000
	class Map
	{
	public:

	private:
		MapHeader header;
		HeightMap heightMap;
		Tile tiles[1];
	};
}
