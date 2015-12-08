#include "Map.hpp"
#include "../Core.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace hpse;

Map::Map(std::uint32_t _width, std::uint32_t _height)
{
	width = _width;
	height = _height;

	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			vertices.push_back((float)i * 1000);
			vertices.push_back(-3.0);
			vertices.push_back(-(float)j * 1000);
		}
	}

	for (std::uint32_t i = 0; i < height; i++)
	{
		for (std::uint32_t j = 0; j < width - 1; j++)
		{
			indices.push_back(i + (j*width));
			indices.push_back(i + (j*width) + width);
			indices.push_back(i + (j*width) + width + 1);

			indices.push_back(i + (j*width));
			indices.push_back(i + (j*width) + width + 1);
			indices.push_back(i + (j*width) + 1);
		}
	}

	Core::GetGraphics()->GetRenderer()->UpdateMap(*this);
}

Map::~Map()
{

}