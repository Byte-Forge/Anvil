#include "Map.hpp"
#include "../Core.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace hpse;

Map::Map(std::uint32_t width, std::uint32_t height)
{
	header.width = width;
	header.height = height;

	heightMap.vertexHeights = (std::int32_t**) malloc(sizeof(std::int32_t*) * width);
	for (std::uint32_t i = 0; i < height; i++)
	{
		heightMap.vertexHeights[i] = (std::int32_t*) malloc(sizeof(std::int32_t) * height);
	}

	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			heightMap.vertexHeights[i][j] = 0;
		}
	}
	//Core::GetGraphics()->GetRenderer()->UpdateMap(*this);
}

Map::~Map()
{

}