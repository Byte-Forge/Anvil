/*
************************************
* Copyright (C) 2016 ByteForge
* RendererGL.hpp
************************************
*/

#pragma once
#include "../IRenderer.hpp"
#include "../../Types/Map.hpp"

namespace anvil
{
	/**
	 * @class	RendererGL
	 *
	 * @brief	A renderer gl.
	 */
	class RendererGL : public IRenderer
	{
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
		 * @fn	void RendererGL::Render(const glm::mat4& ortho);
		 *
		 * @brief	Renders the given ortho.
		 *
		 * @param	ortho	The ortho.
		 */
		void Render(const glm::mat4& ortho);

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

		/**
		 * @fn	void RendererGL::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
		 *
		 * @brief	Called by Rocket when it wants to render geometry that it does not wish to optimise.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param [in,out]	vertices	If non-null, the vertices.
		 * @param	num_vertices		Number of vertices.
		 * @param [in,out]	indices 	If non-null, the indices.
		 * @param	num_indices			Number of indices.
		 * @param	texture				The texture.
		 * @param	translation			The translation.
		 */
		void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices,
			Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

		/**
		 * @fn	Rocket::Core::CompiledGeometryHandle RendererGL::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
		 *
		 * @brief	Called by Rocket when it wants to compile geometry it believes will be static for the
		 * 			forseeable future.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param [in,out]	vertices	If non-null, the vertices.
		 * @param	num_vertices		Number of vertices.
		 * @param [in,out]	indices 	If non-null, the indices.
		 * @param	num_indices			Number of indices.
		 * @param	texture				The texture.
		 *
		 * @return	A Rocket::Core::CompiledGeometryHandle.
		 */
		Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

		/**
		 * @fn	void RendererGL::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		 *
		 * @brief	Called by Rocket when it wants to render application-compiled geometry.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param	geometry   	The geometry.
		 * @param	translation	The translation.
		 */
		void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);

		/**
		 * @fn	void RendererGL::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
		 *
		 * @brief	Called by Rocket when it wants to release application-compiled geometry.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param	geometry	The geometry.
		 */
		void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/**
		 * @fn	void RendererGL::EnableScissorRegion(bool enable);
		 *
		 * @brief	Called by Rocket when it wants to enable or disable scissoring to clip content.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param	enable	true to enable, false to disable.
		 */
		void EnableScissorRegion(bool enable);

		/**
		 * @fn	void RendererGL::SetScissorRegion(int x, int y, int width, int height);
		 *
		 * @brief	Called by Rocket when it wants to change the scissor region.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void SetScissorRegion(int x, int y, int width, int height);

		/**
		 * @fn	bool RendererGL::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		 *
		 * @brief	Called by Rocket when a texture is required by the library.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param [in,out]	texture_handle	  	Handle of the texture.
		 * @param [in,out]	texture_dimensions	The texture dimensions.
		 * @param	source					  	Source for the.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);

		/**
		 * @fn	bool RendererGL::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		 *
		 * @brief	Called by Rocket when a texture is required to be built from an internally-generated
		 * 			sequence of pixels.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param [in,out]	texture_handle	Handle of the texture.
		 * @param	source				  	Source for the.
		 * @param	source_dimensions	  	Source dimensions.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);

		/**
		 * @fn	void RendererGL::ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
		 *
		 * @brief	Called by Rocket when a loaded texture is no longer required.
		 *
		 * @author	Micha
		 * @date	04.03.2016
		 *
		 * @param	texture_handle	Handle of the texture.
		 */
		void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	private:
		int m_totalVRAM;
		std::string m_deviceName;
	};
}