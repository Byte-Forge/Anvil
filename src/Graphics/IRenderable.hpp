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
		std::vector<float> uvs;
		std::vector<float> normals;
		std::vector<std::uint32_t> faces;

		//GL specific stuff
		std::uint32_t mvp;
		std::uint32_t vao;
		std::uint32_t vbo;
		std::uint32_t uvbo;
		std::uint32_t nbo;
		std::uint32_t fbo;

		void Setup();
		void Render();
		void Update();
		void Delete();
	};
}