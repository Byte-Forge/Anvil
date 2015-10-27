#pragma once
#include <memory>
#include "Graphics/IRenderer.hpp"
#include <stdint.h>

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
		void UpdateGUI(int width,int height,const uint8_t* data);
	private: 
		RenderBackend m_backend;
		std::shared_ptr<IRenderer> m_renderer;
	};
}