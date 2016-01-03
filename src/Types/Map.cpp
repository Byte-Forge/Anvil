#include "Map.hpp"
#include "../Graphics/GL/Terrain.hpp"
#include "../Graphics.hpp"
#include "../Core.hpp"
using namespace hpse;

Map::Map()
{
	if(Core::GetCore()->GetGraphics()->GetBackend() == Graphics::OpenGL)
		m_terrain = std::make_shared<GL::Terrain>(200, 200);

	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterRenderable(m_terrain);
}

Map::~Map()
{

}
