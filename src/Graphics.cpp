/*
************************************
* Copyright (C) 2016 ByteForge
* Graphics.cpp
************************************
*/

#include "Graphics.hpp"
#include "Graphics/GL/RendererGL.hpp"
#include "Graphics/GL/Texture.hpp"
#include "Graphics/GL/ModelGL.hpp"
#include "Graphics/GL/MeshGL.hpp"
#ifdef ANVIL_USE_VULKAN
#include "Graphics/VK/RendererVK.hpp"
#endif
#include <glm/gtx/transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "Util/stb_image.h"
#include "Core.hpp"

#include <iostream>

using namespace anvil;

Graphics::Graphics(Graphics::RenderBackend backend) : m_backend(backend), m_available({OpenGL})
{
	switch (backend)
	{
	case OpenGL:
		m_renderer = std::make_shared<RendererGL>();
		break;
	#ifdef ANVIL_USE_VULKAN
	case Vulkan:
		m_renderer = std::make_shared<RendererVK>();
		break;
	#endif
	}

	auto resolution = Core::GetCore()->GetResolution();
	m_ortho = glm::ortho(0.0f, resolution.x, resolution.y, 000.0f);
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

void Graphics::SetRenderer(RenderBackend backend)
{
	if (std::find(m_available.begin(), m_available.end(), backend) != m_available.end())
	{
		switch (backend)
		{
		case OpenGL:
			m_renderer = std::make_shared<RendererGL>();
			break;
		#ifdef ANVIL_USE_VULKAN
		case Vulkan:
			m_renderer = std::make_shared<RendererVK>();
			break;
		#endif
		}
	}
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

std::shared_ptr<IModel> Graphics::GetModel()
{
	std::shared_ptr<IModel> model = nullptr;
	switch (m_backend)
	{
	case OpenGL:
		model = std::make_shared<GL::ModelGL>();
		break;
	default:
		break;
	}
	return model;
}

std::shared_ptr<IMesh> Graphics::GetMesh()
{
	std::shared_ptr<IMesh> mesh = nullptr;
	switch (m_backend)
	{
	case OpenGL:
		mesh = std::make_shared<GL::MeshGL>();
	default:
		break;
	}
	if (mesh == nullptr)
		std::cout << "ERROR!!!!" << std::endl;

	return mesh;
}