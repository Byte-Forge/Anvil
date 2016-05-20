/*
************************************
* Copyright (C) 2016 ByteForge
* RendererVK.hpp
************************************
*/

#pragma once
#include "../IRenderer.hpp"
#include "../../Types/Map.hpp"
#include <vulkan/vulkan.h>

namespace anvil
{
	/**
	 * @class	RendererVK
	 *
	 * @brief	A renderer vk.
	 */
	class RendererVK : public IRenderer
	{
	public:

		/**
		 * @fn	RendererVK::RendererVK();
		 *
		 * @brief	Default constructor.
		 */
		RendererVK();

		/**
		 * @fn	RendererVK::~RendererVK();
		 *
		 * @brief	Destructor.
		 */
		~RendererVK();

		/**
		 * @fn	void RendererVK::Clear();
		 *
		 * @brief	Clears this object to its blank/initial state.
		 */
		void Clear();

		/**
		 * @fn	void RendererVK::Render(const glm::mat4& ortho);
		 *
		 * @brief	Renders the given ortho.
		 *
		 * @param	ortho	The ortho.
		 */
		void Render(const glm::mat4& ortho);

		/**
		 * @fn	void RendererVK::Resize(int width, int height);
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void Resize(int width, int height);

		/**
		 * @fn	void RendererVK::PrintInfo();
		 *
		 * @brief	Print information.
		 */
		void PrintInfo();

		/**
		 * @fn	int RendererVK::GetTotalVRAM();
		 *
		 * @brief	Gets total VRAM.
		 *
		 * @return	The total VRAM.
		 */
		int GetTotalVRAM();

		/**
		 * @fn	int RendererVK::GetUsedVRAM();
		 *
		 * @brief	Gets used VRAM.
		 *
		 * @return	The used VRAM.
		 */
		int GetUsedVRAM();

		/**
		 * @fn	const std::string RendererVK::GetGPUName();
		 *
		 * @brief	Gets GPU name.
		 *
		 * @return	The GPU name.
		 */
		const std::string GetGPUName();

		/**
		 * @fn	void RendererVK::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);
		 *
		 * @brief	Called by Rocket when it wants to render geometry that it does not wish to optimise.
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
		 * @fn	Rocket::Core::CompiledGeometryHandle RendererVK::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);
		 *
		 * @brief	Called by Rocket when it wants to compile geometry it believes will be static for the
		 * 			forseeable future.
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
		 * @fn	void RendererVK::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		 *
		 * @brief	Called by Rocket when it wants to render application-compiled geometry.
		 *
		 * @param	geometry   	The geometry.
		 * @param	translation	The translation.
		 */
		void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);

		/**
		 * @fn	void RendererVK::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);
		 *
		 * @brief	Called by Rocket when it wants to release application-compiled geometry.
		 *
		 * @param	geometry	The geometry.
		 */
		void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/**
		 * @fn	void RendererVK::EnableScissorRegion(bool enable);
		 *
		 * @brief	Called by Rocket when it wants to enable or disable scissoring to clip content.
		 *
		 * @param	enable	true to enable, false to disable.
		 */
		void EnableScissorRegion(bool enable);

		/**
		 * @fn	void RendererVK::SetScissorRegion(int x, int y, int width, int height);
		 *
		 * @brief	Called by Rocket when it wants to change the scissor region.
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void SetScissorRegion(int x, int y, int width, int height);

		/**
		 * @fn	bool RendererVK::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		 *
		 * @brief	Called by Rocket when a texture is required by the library.
		 *
		 * @param [in,out]	texture_handle	  	Handle of the texture.
		 * @param [in,out]	texture_dimensions	The texture dimensions.
		 * @param	source					  	Source for the.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);

		/**
		 * @fn	bool RendererVK::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		 *
		 * @brief	Called by Rocket when a texture is required to be built from an internally-generated
		 * 			sequence of pixels.
		 *
		 * @param [in,out]	texture_handle	Handle of the texture.
		 * @param	source				  	Source for the.
		 * @param	source_dimensions	  	Source dimensions.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);

		/**
		 * @fn	void RendererVK::ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
		 *
		 * @brief	Called by Rocket when a loaded texture is no longer required.
		 *
		 * @param	texture_handle	Handle of the texture.
		 */
		void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);

	private:
		VkSurfaceKHR m_surface;
		VkInstance m_instance;
		VkDevice m_device;
		VkSwapchainKHR m_swapchain;
		VkPhysicalDevice m_physDevice;
		VkPhysicalDeviceFeatures m_gpuFeatures;
		VkPhysicalDeviceProperties m_gpuProperties;
		VkPhysicalDeviceMemoryProperties m_gpuMem;

	private:
		void CreateInstance();
		void CreateDevice();
	};
}