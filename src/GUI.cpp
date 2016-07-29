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
#include <functional>
#include "Exception.hpp"
#include <functional>
#include "Core.hpp"
#include "WorldBuilder.hpp"
#include "Util/Platform.hpp"
#include "Graphics.hpp"
#include "Graphics/IRenderer.hpp"
#include "Core/ResourceHandler.hpp"
#include <GLFW/glfw3.h>

using namespace anvil;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_core(nullptr),m_window(window), m_frameTick(1)
{
	m_core = std::make_unique<spark::Core>(false);

	auto fonts = IO::ListFilesRecursively("ui/fonts/");
	auto defaultFont = fonts.front();

	for (const auto& font : fonts)
	{
		if(!m_core->AddFont(font, font))
			std::cout << "Failed to add font!"<< std::endl;
	}
	
	m_functions["get_fps"] = []() { std::to_string(Core::GetCore()->GetFPS().GetFPS()); };
	m_functions["get_rendered_polygons"] = []() { "Rendered Tris : " + std::to_string(Core::GetCore()->GetGraphics()->GetRenderer()->GetRenderedPolygons()); };
	m_functions["decrease_brush"] = []() { Core::GetCore()->GetWorldBuilder()->DecreaseBrushWidth(); };

	m_view = m_core->CreateView(800, 600, "test.json", m_functions);

	m_updateInterval = (1.0f / UPDATES_PER_SECOND)*1e6;

	m_accumulatedTime = 0;
}

GUI::~GUI()
{
	
}

void GUI::Update()
{
	m_view->Update();
}

void GUI::Render()
{
	int winWidth, winHeight;
	int fbWidth, fbHeight;
	float pxRatio;
	glfwGetWindowSize(m_window, &winWidth, &winHeight);
	glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);

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
	m_view->Resize(width, height);
}

void GUI::MouseMove(int x, int y)
{
	m_view->SetMousePosition(x, y);
}

void GUI::SetMouseState(int key, int action, int mods)
{
	m_view->SetMouseState(key, action, mods);
}

void GUI::KeyDown(int key, int mods)
{
	
}

void GUI::KeyReleased(int key, int mods)
{

}

