#pragma once
#include "../IRenderer.hpp"
#include "./flextGL.h"
#include "../../Types/Map.hpp"

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
		void PrintInfo();

		void Setup(IRenderable &renderable);
		void Render(IRenderable &renderable);
		void Update(IRenderable &renderable);
		void Delete(IRenderable &renderable);
	private:
		GLuint m_guiVbo;
		GLuint m_guiVao;
		GLuint m_guiIbo;
		void SetupGUI();
	};
}