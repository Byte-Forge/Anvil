#include "Terrain.hpp"

using namespace hpse;

Terrain::Terrain(std::uint32_t _width, std::uint32_t _height)
{
	width = _width;
	height = _height;

	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			vertices.push_back((float)i * tileSize);
			vertices.push_back(0.0); //initialize the height with 0 -> flat terrain
			vertices.push_back((float)j * tileSize);

			//create width * height tiles and initialize with default texture
			Tile t = Tile();
			t.tex1 = 0;
			t.tex2 = -1;
			tiles.push_back(t);
		}
	}

	//create the indices needed to render the triangles
	for (std::uint32_t i = 0; i < height; i++)
	{
		for (std::uint32_t j = 0; j < width - 1; j++)
		{
			//first triangle of tile
			indices.push_back(i + (j*width));
			indices.push_back(i + (j*width) + width);
			indices.push_back(i + (j*width) + width + 1);

			//second triangle of tile
			indices.push_back(i + (j*width));
			indices.push_back(i + (j*width) + width + 1);
			indices.push_back(i + (j*width) + 1);
		}
	}
	//create the data needed to render this object
	Setup();
}

Terrain::~Terrain()
{
	//delete all data created to render this object
	Delete();
}