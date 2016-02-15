/*
************************************
* Copyright (C) 2016 ByteForge
* Skybox.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "../ITexture.hpp"
#include "flextGL.h"
#include "../IRenderable.hpp"
#include "Buffer.hpp"


namespace anvil
{
	namespace GL
	{
		class Skybox : public IRenderable
		{
		public:
			Skybox();
			~Skybox();

			void Render(int mode);
			void Update();
		private:
			std::shared_ptr<ITexture> m_diff;
			GLuint m_diffID;

			GLuint m_matrixID;
			GLuint m_CameraPos;

			std::vector<glm::vec3> m_vertices;
			std::vector<std::uint32_t> m_faces;

			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo;
			std::unique_ptr<Buffer> m_fbo;
		};
	}
}