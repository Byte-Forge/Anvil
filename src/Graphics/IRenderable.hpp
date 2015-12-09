#pragma once
#include "IShader.hpp"
#include <vector>
#include <memory>


namespace hpse
{
	class IRenderable
	{
	public:
		std::string vs = "./shader/map.vs";
		std::string fs = "./shader/map.fs";
		std::unique_ptr<IShader> shader;
		std::vector<float> vertices;
		std::vector<int> indices;

		//GL specific stuff
		std::uint32_t vao;
		std::uint32_t vbo;
		std::uint32_t ibo;

		void Setup();
		void Render();
		void Update();
		void Delete();
	};
}