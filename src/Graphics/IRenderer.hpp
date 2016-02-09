#pragma once
#include "IShader.hpp"
#include "IRenderable.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <array>
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

		//GPU info functions
		virtual int GetTotalVRAM() = 0;
		virtual int GetUsedVRAM() = 0;
		virtual const std::string& GetGPUName() = 0;
		

		inline std::uint32_t GetSkyboxUniformLocation(const std::string& id)
		{
			return m_skyboxShader->GetUniformLocation(id);
		}

		inline std::uint32_t GetTerrainUniformLocation(const std::string& id, int mode)
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

		//why do we have to use the 3 here?
		inline std::array<std::string, 3> GetShaderModes()
		{
			return m_shaderModes;
		}

		inline void IncreaseTessellation()
		{
			if (m_tessellationLevel < 64) //above nothing happens
				m_tessellationLevel += 1;
		}

		inline void DecreaseTessellation()
		{
			if (m_tessellationLevel > 1) //should be at least 1
				m_tessellationLevel -= 1;
		}

		inline int GetTessellationLevel()
		{
			return m_tessellationLevel;
		}

	protected:
		int m_tessellationLevel = 32;
		std::array<std::string, 3> m_shaderModes = { "DEFAULT", "WIREFRAME", "NORMALS" };

		bool m_wireframeMode = false;
		bool m_normalsMode = false;

		std::unique_ptr<IShader> m_guiShader;
		std::unique_ptr<IShader> m_skyboxShader;
		std::vector<std::unique_ptr<IShader>> m_terrainShaders;

		std::shared_ptr<IRenderable> m_skybox;
		std::shared_ptr<IRenderable> m_terrain;
		std::vector<std::shared_ptr<IRenderable>> m_renderables;
	};
}