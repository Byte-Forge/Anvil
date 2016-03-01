/*
************************************
* Copyright (C) 2016 ByteForge
* Graphics.hpp
************************************
*/

#pragma once
#include <memory>
#include "Graphics/IRenderer.hpp"
#include "Graphics/IModel.hpp"
#include "Graphics/IMesh.hpp"
#include <stdint.h>
#include <glm/glm.hpp>

namespace anvil
{
	class Graphics
	{
	public:
		enum RenderBackend
		{
			OpenGL = 0,
			#ifdef ANVIL_USE_VULKAN
			Vulkan = 1
			#endif
		};

		 Graphics(RenderBackend = OpenGL);
		 ~Graphics();

		void Clear();
		void Render();
		void Resize(int width, int height);
		void SetRenderer(RenderBackend backend);

		inline void AllowBackend(RenderBackend backend)
		{
			m_available.push_back(backend);
		}

		inline RenderBackend GetBackend()
		{
			return m_backend;
		}

		inline std::shared_ptr<IRenderer> GetRenderer()
		{
			return m_renderer;
		}

		std::shared_ptr<ITexture> GetTexture();
		std::shared_ptr<IModel> GetModel();
		IMesh* GetMesh();

		inline glm::mat4& GetOrtho()
		{
			return m_ortho;
		}
	private: 
		RenderBackend m_backend;
		std::vector<RenderBackend> m_available;
		glm::mat4 m_ortho;
		std::shared_ptr<IRenderer> m_renderer;
	};
}