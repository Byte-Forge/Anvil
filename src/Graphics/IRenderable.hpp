#pragma once
#include "IShader.hpp"
#include "../Core/IResource.hpp"
#include "ITexture.hpp"
#include <glm/glm.hpp>
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
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
		std::vector<std::uint32_t> faces;

		//GL specific stuff
		std::shared_ptr<ITexture> tex;
		std::uint32_t tID;

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