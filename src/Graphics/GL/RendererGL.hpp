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
		void Resize(int width, int height);
	private:
		GLuint m_guiVbo;
		GLuint m_guiVao;
		GLuint m_guiIbo;
		void SetupGUI();
	};
}