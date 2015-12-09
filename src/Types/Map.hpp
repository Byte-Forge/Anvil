#pragma once
#include "Terrain.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

namespace hpse
{
	////////////////////////////////////////////
	//MAP
	////////////////////////////////////////////

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
		std::shared_ptr<Terrain> m_terrain;
		//std::vector<float[2]> playerPositions;

		Map();
		~Map();
	private:

	};
}
