/*
************************************
* Copyright (C) 2016 ByteForge
* Graphics.cpp
************************************
*/

#include "Graphics.hpp"
#include "Graphics/GL/RendererGL.hpp"
#include "Graphics/GL/Texture.hpp"
#include <glm/gtx/transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "Util/stb_image.h"

using namespace anvil;

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

	m_ortho = glm::ortho(0.0f, 800.0f, 600.0f, 000.0f);
}

Graphics::~Graphics()
{

}

void Graphics::Clear()
{
	m_renderer->Clear();
}

void Graphics::Render()
{
	m_renderer->Render(m_ortho);
}

void Graphics::Resize(int width, int height)
{
	m_renderer->Resize(width,height);
	m_ortho = glm::ortho(0.0f, (float)width, (float)height, 000.0f);
}


std::shared_ptr<ITexture> Graphics::GetTexture()
{
	std::shared_ptr<ITexture> tex = nullptr;
	switch(m_backend)
	{
		case OpenGL:
			tex = std::make_shared<GL::Texture>();
			break;
		default:
			break;
	}

	return tex;
}