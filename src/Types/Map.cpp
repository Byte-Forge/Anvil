#include "Map.hpp"

using namespace hpse;

Map::Map()
{
	m_terrain = std::make_unique<Terrain>(40, 40); //default values for default map
}

Map::~Map()
{

}