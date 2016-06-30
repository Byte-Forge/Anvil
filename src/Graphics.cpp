/*
************************************
* Copyright (C) 2016 ByteForge
* Graphics.cpp
************************************
*/

#include "Graphics.hpp"
#include "Graphics/IModel.hpp"
#include "Graphics/IMesh.hpp"
#include "Graphics/GL/RendererGL.hpp"
#include "Graphics/GL/TextureGL.hpp"
#include "Graphics/GL/ModelGL.hpp"
#include "Graphics/GL/MeshGL.hpp"
#ifdef ANVIL_USE_VULKAN
#include "Graphics/VK/RendererVK.hpp"
#endif
#include <glm/gtx/transform.hpp>
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
	m_renderer->Render();
}

void Graphics::Resize(int width, int height)
{
	m_renderer->Resize(width,height);
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
	return mesh;
}
