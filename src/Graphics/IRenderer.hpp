#pragma once
#include "IShader.hpp"
#include "IRenderable.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <Rocket/Core/RenderInterface.h>
#include "../Types/Map.hpp"

namespace hpse
{
	class IRenderer : public Rocket::Core::RenderInterface
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

		inline std::uint32_t GetTerrainUniformLocation(const std::string& id, ShaderMode mode)
		{
			return m_terrainShaders[mode]->GetUniformLocation(id);
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

		inline void ToggleWireframeMode()
		{
			if (m_wireframeMode)
				m_wireframeMode = false;
			else
				m_wireframeMode = true;
		}

		inline void ToggleNormalsMode()
		{
			if (m_normalsMode)
				m_normalsMode = false;
			else
				m_normalsMode = true;
		}

	protected:
		bool m_wireframeMode;
		bool m_normalsMode;

		std::unique_ptr<IShader> m_guiShader;
		std::unique_ptr<IShader> m_skyboxShader;
		std::vector<std::unique_ptr<IShader>> m_terrainShaders;

		std::shared_ptr<IRenderable> m_skybox;
		std::shared_ptr<IRenderable> m_terrain;
		std::vector<std::shared_ptr<IRenderable>> m_renderables;
	};
}