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
#include "Core/Options.hpp"
#include "Exception.hpp"
#include "Core.hpp"
#include "WorldBuilder.hpp"
#include "Util/Platform.hpp"
#include "Graphics.hpp"
#include "Graphics/IRenderer.hpp"
#include "Core/ResourceHandler.hpp"
#include <GLFW/glfw3.h>
#include "Util/FileWatcher.hpp"

using namespace anvil;
namespace fs = boost::filesystem;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_core(nullptr), m_window(window), m_frameTick(1), m_tracked(false)
{
	m_core = std::make_shared<spark::Core>(false);

	//make sure the name is always ui/fonts/Delicious-Bold.otf not ui/fonts\Delicious-Bold.otf !!!!!
	//on all platforms
	auto fonts = IO::ListFilesRecursively("ui/fonts/");
	for (auto& font : fonts)
	{
		std::replace(font.begin(),font.end(),'\\','/');
		if(!m_core->AddFont(font, font))
			std::cout << "Failed to add font!"<< std::endl;
	}

	m_core->AddFunction("get_fps", [](std::shared_ptr<spark::IElement> e) { std::dynamic_pointer_cast<spark::Label> (e)->SetText(std::to_string((int)Core::GetCore()->GetFPS().GetFPS())); });
	m_core->AddFunction("get_rendered_tris", [](std::shared_ptr<spark::IElement> e) { std::dynamic_pointer_cast<spark::Label> (e)->SetText("Rendered Tris : " + std::to_string(Core::GetCore()->GetGraphics()->GetRenderer()->GetRenderedPolygons())); });
	
	//main menu
	m_core->AddFunction("singleplayer", [](std::shared_ptr<spark::IElement> e) { std::cout << "singleplayer" << std::endl; });
	m_core->AddFunction("multiplayer", [](std::shared_ptr<spark::IElement> e) { std::cout << "multiplayer" << std::endl; });
	m_core->AddFunction("options", [this](std::shared_ptr<spark::IElement> e) { m_core->GetNamedElement("mainMenu")->Hide(); 
																				m_core->GetNamedElement("options")->Show(); });

	m_core->AddFunction("worldbuilder", [this](std::shared_ptr<spark::IElement> e) {m_core->GetNamedElement("mainMenu")->Hide();
																					m_core->GetNamedElement("worldbuilder")->Show();
																					Core::GetCore()->StartWorldBuilder();
																					Core::GetCore()->SetMode(WORLDBUILDER_MODE); });
	m_core->AddFunction("quit", [](std::shared_ptr<spark::IElement> e) { std::cout << "quit" << std::endl; /*Core::GetCore()->Quit();*/ });

	//options
	m_core->AddFunction("cancel", [this](std::shared_ptr<spark::IElement> e) {	m_core->GetNamedElement("mainMenu")->Show(); m_core->GetNamedElement("options")->Hide(); });
	m_core->AddFunction("default", [this](std::shared_ptr<spark::IElement> e) { std::cout << "restore to default" << std::endl; });
	m_core->AddFunction("apply", [this](std::shared_ptr<spark::IElement> e) { m_core->GetNamedElement("options")->Hide(); 
																				m_core->GetNamedElement("mainMenu")->Show(); });

	m_core->AddFunction("toggle_fullscreen", [this](std::shared_ptr<spark::IElement> e) { Options::SetFullscreen(std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("fullscreen"))->Toggle()); });
	m_core->AddFunction("toggle_shadows", [this](std::shared_ptr<spark::IElement> e) { Options::SetShadows(std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("shadows"))->Toggle()); });
	m_core->AddFunction("toggle_minRendering", [this](std::shared_ptr<spark::IElement> e) { Options::SetMinimalRendering(std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("minRendering"))->Toggle()); });

	//worldbuilder
	m_core->AddFunction("decrease_brush", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->DecreaseBrushWidth(); });
	m_core->AddFunction("increase_brush", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->IncreaseBrushWidth(); });
	m_core->AddFunction("increase_terrain_height", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->IncreaseBrushHeight(); });
	m_core->AddFunction("decrease_terrain_height", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->DecreaseBrushHeight(); });
	m_core->AddFunction("terrain_mode", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetTerrainMode(); });
	m_core->AddFunction("texture_mode", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetTextureMode(); });
	m_core->AddFunction("entity_mode", [](std::shared_ptr<spark::IElement> e) { Core::GetCore()->GetWorldBuilder()->SetEntityMode(); });



	LoadFile(m_gui_file);

	auto reload = [this](const fs::path &ui_file_path)
	{
		if (m_tracked)
		{
			LoadFile(m_gui_file);
			std::cout << ui_file_path << " was reloaded." << std::endl;
		}
	};

	if (!m_tracked)
	{
		FileWatcher::AddPath(fs::path(m_gui_file),reload);
	}

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
	if (!m_tracked)
		m_tracked = true;
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
	std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("fullscreen"))->SetState(Options::GetFullscreen());
	std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("shadows"))->SetState(Options::GetShadows());
	std::dynamic_pointer_cast<spark::Checkbox> (m_core->GetNamedElement("minRendering"))->SetState(Options::GetMinimalRendering());
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

