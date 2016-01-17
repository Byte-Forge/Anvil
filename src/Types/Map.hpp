#pragma once
#include "../Graphics/IRenderable.hpp"
#include "../Graphics/GL/Terrain.hpp"
#include "../Graphics/GL/Skybox.hpp"
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
		Map();
		~Map();

		inline std::shared_ptr<GL::Terrain>& GetTerrain()
		{
			return m_terrain;
		}

	private:
		std::shared_ptr<GL::Skybox> m_skybox;
		std::shared_ptr<GL::Terrain> m_terrain;
	};
}
