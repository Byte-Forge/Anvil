#pragma once
#include "IOverlay.hpp"
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

		virtual void Resize(int width,int height) = 0;
		virtual void PrintInfo() = 0;

		inline std::uint32_t GetTerrainUniformLocation(char* id)
		{
			return m_terrainShader->GetUniformLocation(id);
		}

		inline void RegisterRenderable(std::shared_ptr<IRenderable> renderable)
		{
			m_renderables.push_back(renderable);
		}

		inline std::unique_ptr<IOverlay>& GetOverlay()
		{
			return m_overlay;
		}
	protected:
		std::unique_ptr<IOverlay> m_overlay;
		std::unique_ptr<IShader> m_guiShader;
		std::unique_ptr<IShader> m_terrainShader;
		std::vector<std::shared_ptr<IRenderable>> m_renderables;
	};
}