#pragma once
#include "ITexture.hpp"
#include "IShader.hpp"
#include "IRenderable.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "../Types/Map.hpp"

namespace hpse
{
	class IRenderer
	{
	public:
		virtual void Clear() = 0;
		virtual void Render(glm::mat4& ortho) = 0;
		inline void UpdateGUI(int width,int height,const uint8_t* data)
		{
			m_overlay->Update(width, height, data);
		}
		virtual void Resize(int width,int height) = 0;
		virtual void PrintInfo() = 0;

		inline void RegisterRenderable(std::shared_ptr<IRenderable> renderable)
		{
			m_renderables.push_back(renderable);
		}
	protected:
		std::unique_ptr<ITexture> m_overlay;
		std::unique_ptr<IShader> m_guiShader;
		std::vector<std::shared_ptr<IRenderable>> m_renderables;
	};
}