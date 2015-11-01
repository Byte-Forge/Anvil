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
		void UpdateGUI(int width,int height,const uint8_t* data);
	private: 
		RenderBackend m_backend;
		glm::mat4 m_ortho;
		std::shared_ptr<IRenderer> m_renderer;
	};
}