#include "GuiRenderer.hpp"
using namespace hpse;

GL::GuiRenderer::GuiRenderer(sf::Window * window) : m_window(window)
{
}

void GL::GuiRenderer::RenderGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices,
	int num_indices, Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f & translation)
{
}

Rocket::Core::CompiledGeometryHandle GL::GuiRenderer::CompileGeometry(Rocket::Core::Vertex * vertices, int num_vertices, int * indices, int num_indices, Rocket::Core::TextureHandle texture)
{
	return Rocket::Core::CompiledGeometryHandle();
}

void GL::GuiRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f & translation)
{
}

void GL::GuiRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
}

void GL::GuiRenderer::EnableScissorRegion(bool enable)
{
}

void GL::GuiRenderer::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, m_window->getSize().y - (y + height), width, height);
}

bool GL::GuiRenderer::LoadTexture(Rocket::Core::TextureHandle & texture_handle, Rocket::Core::Vector2i & texture_dimensions, const Rocket::Core::String & source)
{
	return false;
}

bool GL::GuiRenderer::GenerateTexture(Rocket::Core::TextureHandle & texture_handle, const Rocket::Core::byte * source, const Rocket::Core::Vector2i & source_dimensions)
{
	return false;
}

void GL::GuiRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
}
