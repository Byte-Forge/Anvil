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
		void UpdateMap(Map map);
	private:
		GLuint m_guiVbo;
		GLuint m_guiVao;
		GLuint m_guiIbo;
		void SetupGUI();
		GLuint m_mapVao;
		GLuint m_mapVbo;
		GLuint m_mapIbo;
	};
}