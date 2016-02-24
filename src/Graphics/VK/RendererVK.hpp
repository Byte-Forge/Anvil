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
	class RendererVK : public IRenderer
	{
	public:
		RendererVK();
		~RendererVK();

		void Clear();
		void Render(glm::mat4& ortho);

		void Resize(int width, int height);
		void PrintInfo();

		//GPU info functions
		int GetTotalVRAM();
		int GetUsedVRAM();
		const std::string GetGPUName();

		/// Called by Rocket when it wants to render geometry that it does not wish to optimise.
		void RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices,
			Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation);

		/// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.
		Rocket::Core::CompiledGeometryHandle CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, Rocket::Core::TextureHandle texture);

		/// Called by Rocket when it wants to render application-compiled geometry.
		void RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation);
		/// Called by Rocket when it wants to release application-compiled geometry.
		void ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry);

		/// Called by Rocket when it wants to enable or disable scissoring to clip content.
		void EnableScissorRegion(bool enable);
		/// Called by Rocket when it wants to change the scissor region.
		void SetScissorRegion(int x, int y, int width, int height);

		/// Called by Rocket when a texture is required by the library.
		bool LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source);
		/// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
		bool GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions);
		/// Called by Rocket when a loaded texture is no longer required.
		void ReleaseTexture(Rocket::Core::TextureHandle texture_handle);
	private:
		void CreateInstance();
		void CreateDevice();

		VkSurfaceKHR m_surface;
		VkInstance m_instance;
		VkDevice m_device;
		VkPhysicalDevice m_physDevice;
		VkPhysicalDeviceFeatures m_gpuFeatures;
		VkPhysicalDeviceProperties m_gpuProperties;
		VkPhysicalDeviceMemoryProperties m_gpuMem;
	};
}