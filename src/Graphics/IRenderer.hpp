/*
************************************
* Copyright (C) 2016 ByteForge
* IRenderer.hpp
************************************
*/

#pragma once
#include "IShader.hpp"
#include "IRenderable.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <array>
#include "../Objects/Instance.hpp"
#include "../Core/Options.hpp"

namespace anvil
{
	/**
	 * @class	IRenderer
	 *
	 * @brief	A renderer.
	 */
	class IRenderer 
	{
	public:

		/**
		 * @enum	Vendor
		 *
		 * @brief	Values that represent vendors.
		 */
		enum Vendor
		{
			NVIDIA	= 0,
			AMD		= 1,
			OTHER	= 2,
		};

		/**
		 * @fn	virtual void IRenderer::Clear() = 0;
		 *
		 * @brief	Clears this object to its blank/initial state.
		 */
		virtual void Clear() = 0;

		/**
		 * @fn	virtual void IRenderer::Render(const glm::mat4& ortho) = 0;
		 *
		 * @brief	Renders the given ortho.
		 *
		 * @param	ortho	The ortho.
		 */
		virtual void Render(const glm::mat4& ortho) = 0;

		/**
		 * @fn	virtual void IRenderer::Resize(int width,int height) = 0;
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		virtual void Resize(int width,int height) = 0;

		/**
		 * @fn	virtual void IRenderer::PrintInfo() = 0;
		 *
		 * @brief	Print information.
		 */
		virtual void PrintInfo() = 0;

		/**
		 * @fn	virtual int IRenderer::GetTotalVRAM() = 0;
		 *
		 * @brief	Gets total VRAM.
		 *
		 * @return	The total VRAM.
		 */
		virtual int GetTotalVRAM() = 0;

		/**
		 * @fn	virtual int IRenderer::GetUsedVRAM() = 0;
		 *
		 * @brief	Gets used VRAM.
		 *
		 * @return	The used VRAM.
		 */
		virtual int GetUsedVRAM() = 0;

		/**
		 * @fn	virtual const std::string IRenderer::GetGPUName() = 0;
		 *
		 * @brief	Gets GPU name.
		 *
		 * @return	The GPU name.
		 */
		virtual const std::string GetGPUName() = 0;

		inline void RegisterSkybox(std::shared_ptr<IRenderable> skybox) { m_skybox = skybox; }
		inline void RegisterTerrain(std::shared_ptr<IRenderable> terrain) { m_terrain = terrain; }
		inline void RegisterRenderable(std::shared_ptr<IRenderable> renderable) { m_renderables.push_back(renderable); } 
		inline void RegisterInstance(std::shared_ptr<Instance> instance) { m_instances.push_back(instance); }

		inline void ToggleWireframeMode() {	m_wireframeMode = !m_wireframeMode;	}
		inline void ToggleNormalsMode()	{ m_normalsMode = !m_normalsMode; }

		inline std::array<std::string, 3> GetShaderModes() { return m_shaderModes; }
		inline int GetTessfactor() { return Options::GetTessfactor(); } 
		inline int GetMaxTesselation() { return m_maxTesselation; }
		inline int GetRenderedPolygons() { return m_rendered_polygons; }

	protected:
		int m_rendered_polygons = 0;
		int m_maxTesselation = 64;
		std::array<std::string, 3> m_shaderModes = {{ "DEFAULT", "WIREFRAME", "NORMALS" }};
		Vendor m_vendor;

		bool m_wireframeMode = false;
		bool m_normalsMode = false;

		std::unique_ptr<IShader> m_guiShader;
		std::unique_ptr<IShader> m_skyboxShader;
		std::vector<std::unique_ptr<IShader>> m_terrainShaders;
		std::vector<std::shared_ptr<IShader>> m_modelShaders;

		std::shared_ptr<IRenderable> m_skybox;
		std::shared_ptr<IRenderable> m_terrain;
		std::vector<std::shared_ptr<IRenderable>> m_renderables; 
		std::vector<std::shared_ptr<Instance>> m_instances;
	};
}