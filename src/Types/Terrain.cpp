#include "Terrain.hpp"
#include <iostream>

using namespace hpse;

Terrain::Terrain(std::uint32_t _width, std::uint32_t _height)
{
	width = _width;
	height = _height;

	/*
	// example CUBE for testing
	float size = 1.0f;
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
	faces.push_back(6); faces.push_back(5); faces.push_back(1);

	//back
	faces.push_back(0); faces.push_back(3); faces.push_back(7);
	faces.push_back(0); faces.push_back(4); faces.push_back(7);

	//left
	faces.push_back(0); faces.push_back(1); faces.push_back(5);
	faces.push_back(0); faces.push_back(5); faces.push_back(4);

	//right
	faces.push_back(2); faces.push_back(3); faces.push_back(7);
	faces.push_back(2); faces.push_back(7); faces.push_back(6);
	*/
	
	float uvx;
	float uvy;
	for (std::uint32_t i = 0; i < width; i++)
	{
		//so the uvs change periodically from 0.0 -> 1.0 -> 0.0
		float x = i % 20 / 10.0;
		if (x < 1.0)
			uvx = x;
		else
			uvx = 2 - x;

		for (std::uint32_t j = 0; j < height; j++)
		{
			vertices.push_back({ (float)i * tileSize, glm::sin(i + j)* (j % 3) + glm::cos(j) * (i % 4), (float)j * tileSize });

			//so the uvs change periodically from 0.0 -> 1.0 -> 0.0
			float y = (j % 20 / 10.0);
			if (y < 1.0)
				uvy = y;
			else
				uvy = 2 - y;

			uvs.push_back({uvx, uvy});
 
			normals.push_back({ 0.0, 1.0, 0.0 });
		}
	}
	
	//create the indices needed to render the triangles
	for (std::uint32_t i = 0; i < height - 1; i++)
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

	//create the data needed to render this object
	Setup();
}

Terrain::~Terrain()
{
	//delete all data created to render this object
	Delete();
}