/*
************************************
* Copyright (C) 2016 ByteForge
* Map.hpp
************************************
*/

#pragma once
#include "../Graphics/IRenderable.hpp"
#include "../Graphics/GL/TerrainGL.hpp"
#include "../Graphics/GL/SkyboxGL.hpp"
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

namespace anvil
{
	/**
	 * @class	Map
	 *
	 * @brief	A map.
	 */
	class Map
	{
	public:

		/**
		 * @fn	Map::Map();
		 *
		 * @brief	Default constructor.
		 */
		Map();
		~Map();

		inline std::shared_ptr<GL::Terrain>& GetTerrain() { return m_terrain; }

	private:
		std::shared_ptr<GL::Skybox> m_skybox;
		std::shared_ptr<GL::Terrain> m_terrain;
	};
}
