#ifdef ANVIL_USE_VULKAN
#include "RendererVK.hpp"
#include <GLFW/glfw3.h>
#include "../../Core.hpp"
using namespace anvil;

RendererVK::RendererVK()
{
	auto* window = Core::GetCore()->GetWindow();
	PFN_vkCreateDevice pfnCreateDevice = (PFN_vkCreateDevice)glfwGetInstanceProcAddress(0, "vkCreateDevice");
	
}

RendererVK::~RendererVK()
{

}

void RendererVK::Clear()
{

}

void RendererVK::Render(glm::mat4 & ortho)
{
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