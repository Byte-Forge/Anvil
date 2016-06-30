/*
************************************
* Copyright (C) 2016 ByteForge
* GUI.cpp
************************************
*/

#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"
#include <iostream>
#include "Exception.hpp"
#include <functional>
#include "Core.hpp"
#include "Util/Platform.hpp"
#include "Graphics.hpp"
#include "Graphics/IRenderer.hpp"
#include <GLFW/glfw3.h>

using namespace anvil;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_core(nullptr),m_window(window), m_frameTick(1)
{
	m_core = std::make_unique<spark::Core>(false);

	auto fonts = IO::ListFiles("ui/fonts/");
	auto defaultFont = fonts.front();

	for (const auto& font : fonts)
	{
		std::cout << font << std::endl;
		if(!m_core->AddFont(font, "ui/fonts/" + font))
			std::cout << "Failed to add font!"<< std::endl;
	}
	
	m_view = m_core->CreateView(800, 600);
	auto element = std::make_shared<spark::Grid>();	
	m_fps = std::make_shared<spark::ILabel>();
	m_fps->SetText("0");
	m_fps->SetFontSize(26.0f);
	m_fps->SetFont(defaultFont);
	element->AddChildren(m_fps);

	m_renderedTris = std::make_shared<spark::ILabel>();
	m_renderedTris->SetText("0");
	m_renderedTris->SetFontSize(26.0f);
	m_renderedTris->SetFont(defaultFont);
	m_renderedTris->SetMargin(spark::vec4<unsigned int>(30, 0, 0, 0));
	element->AddChildren(m_renderedTris);
	
	m_view->SetRoot(element);

	m_updateInterval = (1.0f / UPDATES_PER_SECOND)*1e6;

	m_accumulatedTime = 0;
}

GUI::~GUI()
{
	
}

void GUI::Update()
{
}

void GUI::Render()
{
	int winWidth, winHeight;
	int fbWidth, fbHeight;
	float pxRatio;
	glfwGetWindowSize(m_window, &winWidth, &winHeight);
	glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);

	//Set FPS
	int fps = Core::GetCore()->GetFPS().GetFPS();
	m_fps->SetText("FPS: " + std::to_string(fps));

	//set rendered tris
	int rtris = Core::GetCore()->GetGraphics()->GetRenderer()->GetRenderedPolygons();
	m_renderedTris->SetText("Rendered Tris: " + std::to_string(rtris));

	// Calculate pixel ration for hi-dpi devices.
	pxRatio = (float)fbWidth / (float)winWidth;

	spark::PaintEvent ev;
	ev.context = m_core->GetPaintContext();
	ev.ratio = pxRatio;
	m_view->Render(ev);
}

void GUI::LoadFile(const std::string& file)
{
	
}

void GUI::Resize(int width, int height)
{

}

void GUI::MouseMove(int x, int y, int mods)
{
	
}

void GUI::MousePressed(int key, int mods)
{
	
}

void GUI::MouseReleased(int key, int mods)
{
	
}

void GUI::KeyDown(int key, int mods)
{
	
}

void GUI::KeyReleased(int key, int mods)
{
}

