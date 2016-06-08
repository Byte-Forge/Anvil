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