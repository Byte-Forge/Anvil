#include "Graphics.hpp"
#include "Graphics/RendererGL.hpp"
using namespace hpse;

Graphics::Graphics(Graphics::RenderBackend backend) : m_backend(backend)
{
	switch (backend)
	{
	case OpenGL:
		m_renderer = std::make_shared<RendererGL>();
		break;
	case Vulkan:
		break;
	}
}

Graphics::~Graphics()
{

}

void Graphics::Clear()
{
	m_renderer->Clear();
}

void Graphics::UpdateGUI(int width, int height, const uint8_t *data)
{
	m_renderer->UpdateGUI(width,height,data);
}

void Graphics::Render()
{
	m_renderer->Render();
}