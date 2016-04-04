/*
************************************
* Copyright (C) 2016 ByteForge
* RendererVK.cpp
************************************
*/
#ifdef ANVIL_USE_VULKAN
#include "RendererVK.hpp"
#include <GLFW/glfw3.h>
#include "../../Core.hpp"
#include "../../Exception.hpp"
#include "Debug.hpp"
using namespace anvil;

RendererVK::RendererVK() : m_instance(nullptr), m_device(nullptr), m_physDevice(nullptr), m_surface(nullptr)
{
	auto* window = Core::GetCore()->GetWindow();
	CreateInstance();
	#ifndef NDEBUG
	vk::setupDebugging(m_instance, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, NULL);
	#endif
	CreateDevice();

	vkGetPhysicalDeviceFeatures(m_physDevice, &m_gpuFeatures);
	vkGetPhysicalDeviceProperties(m_physDevice, &m_gpuProperties);
	// Gather physical device memory properties
	vkGetPhysicalDeviceMemoryProperties(m_physDevice, &m_gpuMem);

	VkResult success = glfwCreateWindowSurface(m_instance, window, NULL, &m_surface);

}

void RendererVK::CreateInstance()
{
	VkResult result = VK_SUCCESS;
	VkApplicationInfo app = {};
	app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	app.pApplicationName = "Anvil-test";
	app.pEngineName = "Anvil";
	app.apiVersion = VK_API_VERSION;

	unsigned int extCount;
	const char** glfwExtension = glfwGetRequiredInstanceExtensions(&extCount);
	std::vector<const char*> extensions(glfwExtension, glfwExtension+extCount);
	#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	#endif
	VkInstanceCreateInfo ici = {};
	ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	ici.pApplicationInfo = &app;
	ici.enabledExtensionCount = extensions.size();
	ici.ppEnabledExtensionNames = extensions.data();
	#ifndef NDEBUG
	ici.enabledLayerCount = vk::validationLayerCount;
	ici.ppEnabledLayerNames = vk::validationLayerNames;
	#endif

	result = vkCreateInstance(&ici, NULL, &m_instance);
	if (result != VK_SUCCESS)
		throw AnvilException("Failed to create vulkan instance!", __FILE__, __LINE__);
}

void RendererVK::CreateDevice()
{
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(m_instance, &count, NULL);
	std::vector<VkPhysicalDevice> physDevices;
	physDevices.resize(count);
	vkEnumeratePhysicalDevices(m_instance, &count, physDevices.data());

	std::array<float, 1> queuePriorities = { 0.0f };
	VkDeviceQueueCreateInfo dqci = {};

	//pick the first device that allows presentation
	for (const auto& cDevice : physDevices)
	{
		uint32_t cQueue = 0;
		uint32_t queueCount;
		vkGetPhysicalDeviceQueueFamilyProperties(cDevice, &queueCount, NULL);
		bool foundDevice = false;

		std::vector<VkQueueFamilyProperties> queueProps;
		queueProps.resize(queueCount);
		vkGetPhysicalDeviceQueueFamilyProperties(cDevice, &queueCount, queueProps.data());

		for (cQueue = 0;cQueue < queueCount;++cQueue)
		{
			if (glfwGetPhysicalDevicePresentationSupport(m_instance, cDevice, cQueue))
			{
				m_physDevice = cDevice;
				foundDevice = true;
				break;
			}
		}

		if (!foundDevice)
			continue;

		dqci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		dqci.queueFamilyIndex = cQueue;
		dqci.queueCount = queueCount;
		dqci.pQueuePriorities = queuePriorities.data();
		break;
	}

	if (!m_physDevice)
		throw AnvilException("No suitable device found", __FILE__, __LINE__);

	VkDeviceCreateInfo dci = {};
	dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	#ifndef NDEBUG
	dci.enabledLayerCount = vk::validationLayerCount;
	dci.ppEnabledLayerNames = vk::validationLayerNames;
	#endif
	dci.queueCreateInfoCount = 1;
	dci.pQueueCreateInfos = &dqci;

	vkCreateDevice(m_physDevice, &dci, NULL, &m_device);
}


RendererVK::~RendererVK()
{
	#ifndef NDEBUG
	vk::freeDebugCallback(m_instance);
	#endif

	if (m_surface)
		vkDestroySurfaceKHR(m_instance, m_surface, NULL);
	if(m_device)
		vkDestroyDevice(m_device, NULL);
	if(m_instance)
		vkDestroyInstance(m_instance, NULL);
	
}

void RendererVK::Clear()
{

}

void RendererVK::Render(const glm::mat4 & ortho)
{
	VkResult  err;
	VkSemaphore presentCompleteSemaphore;
	VkSemaphoreCreateInfo presentCompleteSemaphoreCreateInfo = {};
	presentCompleteSemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	presentCompleteSemaphoreCreateInfo.pNext = NULL;
	presentCompleteSemaphoreCreateInfo.flags = 0;


	err = vkCreateSemaphore(m_device, &presentCompleteSemaphoreCreateInfo,	NULL, &presentCompleteSemaphore);

	
}

void RendererVK::Resize(int width, int height)
{
}

void RendererVK::PrintInfo()
{
}

int RendererVK::GetTotalVRAM()
{
	return 0;
}

int RendererVK::GetUsedVRAM()
{
	return 0;
}

const std::string RendererVK::GetGPUName()
{
	return std::string();
}

void RendererVK::RenderGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f & translation)
{
}

Rocket::Core::CompiledGeometryHandle RendererVK::CompileGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	return Rocket::Core::CompiledGeometryHandle();
}

void RendererVK::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f & translation)
{
}

void RendererVK::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
}

void RendererVK::EnableScissorRegion(bool enable)
{
}

void RendererVK::SetScissorRegion(int x, int y, int width, int height)
{
}

bool RendererVK::LoadTexture(Rocket::Core::TextureHandle & texture_handle, Rocket::Core::Vector2i & texture_dimensions, const Rocket::Core::String & source)
{
	return false;
}

bool RendererVK::GenerateTexture(Rocket::Core::TextureHandle & texture_handle, const Rocket::Core::byte * source, const Rocket::Core::Vector2i & source_dimensions)
{
	return false;
}

void RendererVK::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
}


#endif