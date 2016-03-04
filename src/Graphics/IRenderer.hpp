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
#include <Rocket/Core/RenderInterface.h>
#include "../Types/Map.hpp"

namespace anvil
{
	/**
	 * @class	IRenderer
	 *
	 * @brief	A renderer.
	 */
	class IRenderer : public Rocket::Core::RenderInterface
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
		 * @fn	virtual void IRenderer::Render(glm::mat4& ortho) = 0;
		 *
		 * @brief	Renders the given ortho.
		 *
		 * @param [in,out]	ortho	The ortho.
		 */
		virtual void Render(glm::mat4& ortho) = 0;

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

		inline void ToggleWireframeMode() {	m_wireframeMode = !m_wireframeMode;	}
		inline void ToggleNormalsMode()	{ m_normalsMode = !m_normalsMode; }

		///why do we have to use the 3 here? where is this called?
		inline std::array<std::string, 3> GetShaderModes() { return m_shaderModes; }
		inline int GetTessfactor() { return m_tessFactor; } 
		inline int GetMaxTesselation() { return m_maxTesselation; }

	protected:
		int m_tessFactor = 32;
		int m_maxTesselation = 64;
		std::array<std::string, 3> m_shaderModes = {{ "DEFAULT", "WIREFRAME", "NORMALS" }};
		Vendor m_vendor;

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