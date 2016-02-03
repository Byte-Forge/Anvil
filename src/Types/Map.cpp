#include "Map.hpp"
#include "../Graphics/GL/Terrain.hpp"
#include "../Graphics.hpp"
#include "../Core.hpp"
using namespace hpse;

Map::Map()
{
	if (Core::GetCore()->GetGraphics()->GetBackend() == Graphics::OpenGL)
	{
		m_skybox = std::make_shared<GL::Skybox>();
		m_terrain = std::make_shared<GL::Terrain>(2000, 2000);
	}

	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterSkybox(m_skybox);
	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterTerrain(m_terrain);
}

Map::~Map()
{

}
