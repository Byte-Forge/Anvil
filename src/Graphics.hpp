/*
************************************
* Copyright (C) 2016 ByteForge
* Graphics.hpp
************************************
*/

#pragma once
#include <memory>
#include "Graphics/IRenderer.hpp"
#include <stdint.h>
#include <glm/glm.hpp>

namespace anvil
{
	class IModel;
	class IMesh;

	/**
	 * @class	Graphics
	 *
	 * @brief	A graphics.
	 */
	class Graphics
	{
	public:

		/**
		 * @enum	RenderBackend
		 *
		 * @brief	Values that represent render backends OpenGL or Vulkan.
		 */
		enum RenderBackend
		{
			OpenGL = 0,
			#ifdef ANVIL_USE_VULKAN
			Vulkan = 1
			#endif
		};

		 /**
		  * @fn	Graphics::Graphics(RenderBackend = OpenGL);
		  *
		  * @brief	Constructor.
		  *
		  * @param	parameter1	the default backend to use (OpenGL).
		  */
		Graphics(RenderBackend = OpenGL);

		 /**
		  * @fn	Graphics::~Graphics();
		  *
		  * @brief	Destructor.
		  */
		~Graphics();

		/**
		 * @fn	void Graphics::Clear();
		 *
		 * @brief	Clears this object to its blank/initial state.
		 *
		 * @author	Micha
		 * @date	02.03.2016
		 */
		void Clear();

		/**
		 * @fn	void Graphics::Render();
		 *
		 * @brief	Renders the whole scene.
		 */
		void Render();

		/**
		 * @fn	void Graphics::Resize(int width, int height);
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void Resize(int width, int height);

		/**
		 * @fn	void Graphics::SetRenderer(RenderBackend backend);
		 *
		 * @brief	Sets a renderer.
		 *
		 * @param	backend	The backend.
		 */
		void SetRenderer(RenderBackend backend);

		/**
		 * @fn	std::shared_ptr<ITexture> Graphics::GetTexture();
		 *
		 * @brief	Gets the texture.
		 *
		 * @return	a texture pointer dependand on the render backend.
		 */
		std::shared_ptr<ITexture> GetTexture();

		/**
		 * @fn	std::shared_ptr<IModel> Graphics::GetModel();
		 *
		 * @brief	Gets the model.
		 *
		 * @return	A model object dependand on the render backend.
		 */
		std::shared_ptr<IModel> GetModel();

		/**
		 * @fn	std::shared_ptr<IMesh> Graphics::GetMesh();
		 *
		 * @brief	Gets the mesh.
		 *
		 * @return	A mesh object dependend on the render backend.
		 */
		std::shared_ptr<IMesh> GetMesh();

		inline void AllowBackend(RenderBackend backend) { m_available.push_back(backend); }
		inline RenderBackend GetBackend() { return m_backend; }
		inline std::shared_ptr<IRenderer> GetRenderer() { return m_renderer; }
		inline glm::mat4& GetOrtho() { return m_ortho; }

	private: 
		RenderBackend m_backend;
		std::vector<RenderBackend> m_available;
		glm::mat4 m_ortho;
		std::shared_ptr<IRenderer> m_renderer;
	};
}