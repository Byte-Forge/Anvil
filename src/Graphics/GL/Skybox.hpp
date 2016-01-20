#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "../ITexture.hpp"
#include "flextGL.h"
#include "../IRenderable.hpp"


namespace hpse
{
	namespace GL
	{
		class Skybox : public IRenderable
		{
		public:
			Skybox();
			~Skybox();

			void Render(ShaderMode mode);
			void Update();
		private:
			std::shared_ptr<ITexture> m_diff;
			GLuint m_diffID;

			GLuint m_matrixID;
			GLuint m_CameraPos;

			std::vector<glm::vec3> m_vertices;
			std::vector<glm::vec3> m_normals;
			std::vector<glm::vec2> m_uvs;
			std::vector<std::uint32_t> m_faces;

			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_uvbo;
			GLuint m_nbo;
			GLuint m_fbo;
		};
	}
}