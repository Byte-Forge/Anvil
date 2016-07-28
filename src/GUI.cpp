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
		std::cout << font << std::endl;
		if(!m_core->AddFont(font, font))
			std::cout << "Failed to add font!"<< std::endl;
	}
	
	m_view = m_core->CreateView(800, 600);

	auto element = std::make_shared<spark::Grid>();	

	m_fps = std::make_shared<spark::ILabel>();
	m_fps->SetText("0");
	m_fps->SetBorderSize(0.0);
	m_fps->SetBackgroundColor(spark::vec4<unsigned int>(0, 0, 0, 0));
	m_fps->SetFontSize(26.0f);
	m_fps->SetFont(defaultFont);
	element->AddChildren(m_fps);

	m_renderedTris = std::make_shared<spark::ILabel>();
	m_renderedTris->SetText("0");
	m_renderedTris->SetFontSize(26.0f);
	m_renderedTris->SetBorderSize(0.0);
	m_renderedTris->SetBackgroundColor(spark::vec4<unsigned int>(0, 0, 0, 0));
	m_renderedTris->SetFont(defaultFont);
	m_renderedTris->SetMargin(spark::vec4<unsigned int>(30, 0, 0, 0));
	element->AddChildren(m_renderedTris);

	std::string imgpath;
	std::function<void()> f;

	//WB buttons
	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/decrease_brush_width.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->DecreaseBrushWidth(); };
	//m_decrease_brush_button = std::make_shared<spark::IButton>(imgpath);
	//m_decrease_brush_button->SetFunction(f);
	//m_decrease_brush_button->SetWidth(50);
	//m_decrease_brush_button->SetHeight(50);
	//m_decrease_brush_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 750));
	//m_decrease_brush_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_decrease_brush_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/increase_brush_width.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->IncreaseBrushWidth(); };
	//m_increase_brush_button = std::make_shared<spark::IButton>(imgpath);
	//m_increase_brush_button->SetFunction(f);
	//m_increase_brush_button->SetWidth(50);
	//m_increase_brush_button->SetHeight(50);
	//m_increase_brush_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 700));
	//m_increase_brush_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_increase_brush_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/increase_terrain_height.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->IncreaseBrushHeight(); };
	//m_increase_brush_height_button = std::make_shared<spark::IButton>(imgpath);
	//m_increase_brush_height_button->SetFunction(f);
	//m_increase_brush_height_button->SetWidth(50);
	//m_increase_brush_height_button->SetHeight(50);
	//m_increase_brush_height_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 650));
	//m_increase_brush_height_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_increase_brush_height_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/decrease_terrain_height.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->DecreaseBrushHeight(); };
	//m_decrease_brush_height_button = std::make_shared<spark::IButton>(imgpath);
	//m_decrease_brush_height_button->SetFunction(f);
	//m_decrease_brush_height_button->SetWidth(50);
	//m_decrease_brush_height_button->SetHeight(50);
	//m_decrease_brush_height_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 600));
	//m_decrease_brush_height_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_decrease_brush_height_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/terrain_mode.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->SetTerrainMode(); };
	//m_terrain_mode_button = std::make_shared<spark::IButton>(imgpath);
	//m_terrain_mode_button->SetFunction(f);
	//m_terrain_mode_button->SetWidth(50);
	//m_terrain_mode_button->SetHeight(50);
	//m_terrain_mode_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 550));
	//m_terrain_mode_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_terrain_mode_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/texture_mode.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->SetTextureMode(); };
	//m_texture_mode_button = std::make_shared<spark::IButton>(imgpath);
	//m_texture_mode_button->SetFunction(f);
	//m_texture_mode_button->SetWidth(50);
	//m_texture_mode_button->SetHeight(50);
	//m_texture_mode_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 500));
	//m_texture_mode_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_texture_mode_button);

	//Core::GetCore()->GetResources()->GetFilePath("ui/buttons/entity_mode.png", imgpath);
	//f = []() { Core::GetCore()->GetWorldBuilder()->SetEntityMode(); };
	//m_entity_mode_button = std::make_shared<spark::IButton>(imgpath);
	//m_entity_mode_button->SetFunction(f);
	//m_entity_mode_button->SetWidth(50);
	//m_entity_mode_button->SetHeight(50);
	//m_entity_mode_button->SetMargin(spark::vec4<unsigned int>(0, 0, 0, 450));
	//m_entity_mode_button->SetBackgroundColor(spark::vec4<unsigned int>(255, 0, 0, 255));
	//element->AddChildren(m_entity_mode_button);


	//Core::GetCore()->GetResources()->GetFilePath("ui/gondor.png", imgpath);
	//m_image = std::make_shared<spark::IImage>(imgpath);
	//m_image->SetWidth(400);
	//m_image->SetHeight(250);
	//m_image->SetMargin(spark::vec4<unsigned int>(350, 0, 0, 0));
	//element->AddChildren(m_image);

	m_view->SetRoot(element);

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

