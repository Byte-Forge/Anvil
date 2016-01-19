#pragma once
#include "IOverlay.hpp"
#include "IShader.hpp"
#include "IRenderable.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <Rocket/Core/RenderInterface.h>
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

		inline std::uint32_t GetSkyboxUniformLocation(const std::string& id)
		{
			return m_skyboxShader->GetUniformLocation(id);
		}

		inline std::uint32_t GetTerrainUniformLocation(const std::string& id)
		{
			return m_terrainShader->GetUniformLocation(id);
		}

		inline std::uint32_t GetGuiUniformLocation(const std::string& id)
		{
			return m_guiShader->GetUniformLocation(id);
		}

		inline void RegisterSkybox(std::shared_ptr<IRenderable> skybox)
		{
			m_skybox = skybox;
		}

		inline void RegisterTerrain(std::shared_ptr<IRenderable> terrain)
		{
			m_terrain = terrain;
		}

		inline void RegisterRenderable(std::shared_ptr<IRenderable> renderable)
		{
			m_renderables.push_back(renderable);
		}

		inline std::unique_ptr<IOverlay>& GetOverlay()
		{
			return m_overlay;
		}

		inline std::unique_ptr<Rocket::Core::RenderInterface>& GetRocketRenderer()
		{
			return m_rocketrenderer;
		}

		inline void UseGuiShader()
		{
			m_guiShader->Use();
		}
	protected:
		std::unique_ptr<IOverlay> m_overlay;
		std::unique_ptr<IShader> m_guiShader;
		std::unique_ptr<IShader> m_skyboxShader;
		std::unique_ptr<IShader> m_terrainShader;

		std::shared_ptr<IRenderable> m_skybox;
		std::shared_ptr<IRenderable> m_terrain;
		std::unique_ptr<Rocket::Core::RenderInterface> m_rocketrenderer;
		std::vector<std::shared_ptr<IRenderable>> m_renderables;
	};
}