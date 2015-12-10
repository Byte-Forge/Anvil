#include "Terrain.hpp"

using namespace hpse;

Terrain::Terrain(std::uint32_t _width, std::uint32_t _height)
{
	width = _width;
	height = _height;

	// example CUBE for testing
	float size = 2.0f;
	vertices.push_back({ -size, -size, -size });
	vertices.push_back({ -size, -size, size });
	vertices.push_back({ size, -size, size });
	vertices.push_back({ size, -size, -size });

	vertices.push_back({ -size, size, -size });
	vertices.push_back({ -size, size, size });
	vertices.push_back({ size, size, size });
	vertices.push_back({ size, size, -size });

	//bottom
	faces.push_back(0); faces.push_back(1); faces.push_back(2);
	faces.push_back(0); faces.push_back(2); faces.push_back(3);

	//top
	faces.push_back(4); faces.push_back(5); faces.push_back(6);
	faces.push_back(4); faces.push_back(6); faces.push_back(7);

	//front
	faces.push_back(1); faces.push_back(2); faces.push_back(6);
	faces.push_back(1); faces.push_back(5); faces.push_back(6);

	//back
	faces.push_back(0); faces.push_back(3); faces.push_back(7);
	faces.push_back(0); faces.push_back(4); faces.push_back(7);

	//left
	faces.push_back(0); faces.push_back(1); faces.push_back(5);
	faces.push_back(0); faces.push_back(5); faces.push_back(4);

	//right
	faces.push_back(2); faces.push_back(3); faces.push_back(7);
	faces.push_back(2); faces.push_back(7); faces.push_back(6);

	/*
	for (std::uint32_t i = 0; i < width; i++)
	{
		for (std::uint32_t j = 0; j < height; j++)
		{
			vertices.push_back({ (float)i * tileSize, -1.0 * (i*j) / 10.0, -(float)j * tileSize });

			//create width * height tiles and initialize with default texture
			//Tile t = Tile();
			//t.tex1 = 0;
			//t.tex2 = -1;
			//tiles.push_back(t);
		}
	}

	//create the indices needed to render the triangles
	for (std::uint32_t i = 0; i < height; i++)
	{
		for (std::uint32_t j = 0; j < width - 1; j++)
		{
			//first triangle of tile
			faces.push_back(i + (j*width));
			faces.push_back(i + (j*width) + width);
			faces.push_back(i + (j*width) + width + 1);

			//second triangle of tile
			faces.push_back(i + (j*width));
			faces.push_back(i + (j*width) + width + 1);
			faces.push_back(i + (j*width) + 1);
		}
	}
	*/

	//create the data needed to render this object
	Setup();
}

Terrain::~Terrain()
{
	//delete all data created to render this object
	Delete();
}