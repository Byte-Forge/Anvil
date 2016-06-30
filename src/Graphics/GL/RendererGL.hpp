/*
************************************
* Copyright (C) 2016 ByteForge
* RendererGL.hpp
************************************
*/

#pragma once
#include "../IRenderer.hpp"
#include "../../Types/Map.hpp"
#include "UboGL.hpp"
#include "BufferGL.hpp"
#include "FrameBufferGL.hpp"
#include <vector>

namespace anvil
{
	/**
	 * @class	RendererGL
	 *
	 * @brief	A renderer gl.
	 */
	class RendererGL : public IRenderer
	{
	private:
		struct UboData
		{
			glm::mat4 vp;
			glm::mat4 v;
			glm::mat4 depth_vp;
			glm::mat4 depth_bias_vp;

			glm::int32 tess_factor;
			glm::int32 max_tess_factor;

			glm::vec4 cameraPos;
			glm::vec4 lightDir;
			glm::vec4 diffuse;
			glm::vec4 ambient;
			glm::vec4 spec;
		};

	public:

		/**
		 * @fn	RendererGL::RendererGL();
		 *
		 * @brief	Default constructor.
		 */
		RendererGL();

		/**
		 * @fn	RendererGL::~RendererGL();
		 *
		 * @brief	Destructor.
		 */
		~RendererGL();

		/**
		 * @fn	void RendererGL::Clear();
		 *
		 * @brief	Clears this object to its blank/initial state.
		 */
		void Clear();

		/**
		 * @fn	void RendererGL::Render();
		 *
		 * @brief	Renders the given ortho.
		 */
		void Render();

		/**
		 * @fn	void RendererGL::Resize(int width, int height);
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void Resize(int width, int height);

		/**
		 * @fn	void RendererGL::PrintInfo();
		 *
		 * @brief	Print information.
		 */
		void PrintInfo();

		/**
		 * @fn	int RendererGL::GetTotalVRAM();
		 *
		 * @brief	Gets total VRAM.
		 *
		 * @return	The total VRAM.
		 */
		int GetTotalVRAM();

		/**
		 * @fn	int RendererGL::GetUsedVRAM();
		 *
		 * @brief	Gets used VRAM.
		 *
		 * @return	The used VRAM.
		 */
		int GetUsedVRAM();

		/**
		 * @fn	const std::string RendererGL::GetGPUName();
		 *
		 * @brief	Gets GPU name.
		 *
		 * @return	The GPU name.
		 */
		const std::string GetGPUName();

	private:
		bool m_render2buffer = true; 
		bool m_renderShadows = true;
		int m_totalVRAM;
		std::string m_deviceName;

		std::unique_ptr<GL::FrameBuffer> m_frameBuffer;
		std::unique_ptr<GL::FrameBuffer> m_shadowBuffer;

		UboData m_ubo_data;
		GL::UniformBuffer<UboData> m_ubo;

		std::unique_ptr<GL::Buffer> m_quad_vbo;
	};
}