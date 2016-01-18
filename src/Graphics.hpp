#pragma once
#include <memory>
#include "Graphics/IRenderer.hpp"
#include <stdint.h>
#include <glm/glm.hpp>

namespace hpse
{
	class Graphics
	{
	public:
		enum RenderBackend
		{
			OpenGL = 0,
			Vulkan = 1
		};

		 Graphics(RenderBackend = OpenGL);
		 ~Graphics();

		void Clear();
		void Render();
		void Resize(int width, int height);

		inline RenderBackend GetBackend()
		{
			return m_backend;
		}

		inline std::shared_ptr<IRenderer> GetRenderer()
		{
			return m_renderer;
		}
		std::shared_ptr<ITexture> GetTexture();

		inline glm::mat4& GetOrtho()
		{
			return m_ortho;
		}
	private: 
		RenderBackend m_backend;
		glm::mat4 m_ortho;
		std::shared_ptr<IRenderer> m_renderer;
	};
}