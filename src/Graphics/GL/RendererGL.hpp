#pragma once
#include "../IRenderer.hpp"
#include "./flextGL.h"
namespace hpse
{
	class RendererGL : public IRenderer
	{
	public:
		RendererGL();
		~RendererGL();

		void Clear();
		void Render(glm::mat4& ortho);

	private:
		GLuint m_guiVbo;
	};
}