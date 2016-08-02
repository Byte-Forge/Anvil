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
#include "Util/Watchdog.h"

using namespace anvil;
namespace fs = boost::filesystem;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_core(nullptr), m_window(window), m_frameTick(1), m_tracked(false)
{
	m_core = std::make_shared<spark::Core>(false);

	//make sure the name is always ui/fonts/Delicious-Bold.otf not ui/fonts\Delicious-Bold.otf !!!!!
	//on all platforms
	auto fonts = IO::ListFilesRecursively("ui/fonts/");
	for (const auto& font : fonts)
	{
		if(!m_core->AddFont(font, font))
			std::cout << "Failed to add font!"<< std::endl;
	}

	std::string func_name = "get_fps";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { std::dynamic_pointer_cast<spark::ILabel> (e)->SetText(std::to_string((int)Core::GetCore()->GetFPS().GetFPS())); });
	func_name = "get_rendered_tris";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { std::dynamic_pointer_cast<spark::ILabel> (e)->SetText("Rendered Tris : " + std::to_string(Core::GetCore()->GetGraphics()->GetRenderer()->GetRenderedPolygons())); });
	func_name = "decrease_brush";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->DecreaseBrushWidth(); });
	func_name = "increase_brush";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->IncreaseBrushWidth(); });
	func_name = "increase_terrain_height";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->IncreaseBrushHeight(); });
	func_name = "decrease_terrain_height";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->DecreaseBrushHeight(); });
	func_name = "terrain_mode";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetTerrainMode(); });
	func_name = "texture_mode";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetTextureMode(); });
	func_name = "entity_mode";
	m_core->AddFunction(func_name, [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetEntityMode(); });

	LoadFile(m_gui_file);

	if (m_view == nullptr)
		throw AnvilException("Failed to load UI file: " + m_gui_file, __FILE__, __LINE__);

	m_updateInterval = (1.0f / UPDATES_PER_SECOND) * 1e6;

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
	// TODO: combine this with the stuff in core
	pxRatio = (float)fbWidth / (float)winWidth;

	spark::PaintEvent ev;
	ev.context = m_core->GetPaintContext();
	ev.ratio = pxRatio;
	m_view->Render(ev);
}

void GUI::LoadFile(const std::string& file)
{
	spark::XMLBuilder builder(m_core);
	std::string ui_file_path;
	Core::GetCore()->GetResources()->GetFilePath(m_gui_file, ui_file_path);
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	auto view = builder.LoadView(width, height, ui_file_path);
	if (view != nullptr)
		m_view = view;

	auto reload = [this](const fs::path &ui_file_path) {
		if (m_tracked)
		{
			std::cout << ui_file_path << " needs reload" << std::endl;
			LoadFile(m_gui_file);
		}
	};

	if (!m_tracked)
	{
		wd::watch(fs::path(ui_file_path), reload);
	}
	m_tracked = true;
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

