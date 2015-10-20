#pragma once
#include <memory>
#include "Graphics/IRenderer.hpp"

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

	private: 
		RenderBackend m_backend;
		std::shared_ptr<IRenderer> m_renderer;
	};
}