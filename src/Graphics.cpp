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