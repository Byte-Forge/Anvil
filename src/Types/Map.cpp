/*
************************************
* Copyright (C) 2016 ByteForge
* Map.cpp
************************************
*/

#include "Map.hpp"
#include "../Graphics.hpp"
#include "../Core.hpp"

using namespace anvil;

Map::Map()
{
	if (Core::GetCore()->GetGraphics()->GetBackend() == Graphics::OpenGL)
	{
		m_skybox = std::make_shared<GL::Skybox>();
		m_terrain = std::make_shared<GL::Terrain>(600, 600);
	}

	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterSkybox(m_skybox);
	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterTerrain(m_terrain);
}

Map::~Map()
{

}
