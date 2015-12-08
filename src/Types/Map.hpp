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
		//size is (width + borderSize * 2) * (height + borderSize * 2);
		std::int32_t **vertexHeights;
	};

	// chunk 0x80000001
	struct MapHeader 
	{
		std::uint32_t width;
		std::uint32_t height;
		float playerPositions[1][2];
		std::string textures[1];
	};


	class Map
	{
	public:
		std::uint32_t width;
		std::uint32_t height;
		//std::vector<float[2]> playerPositions;
		std::vector<std::string> textures;
		std::vector<float> vertices;
		std::vector<int> indices;

		Map(std::uint32_t width, std::uint32_t height);
		~Map();
	private:

	};
}
