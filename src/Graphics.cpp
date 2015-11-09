#include "Graphics.hpp"
#include "Graphics/GL/RendererGL.hpp"
#include <glm/gtx/transform.hpp>
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

	m_ortho = glm::ortho(0.0f, 0.0f, 800.0f, 600.0f,0.1f,100.0f);
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
	m_renderer->Render(m_ortho);
}

void hpse::Graphics::Resize(int width, int height)
{
	m_renderer->Resize(width,height);
	m_ortho = glm::ortho(0.0f, 0.0f, (float)width, (float)height, 0.1f, 100.0f);
}
