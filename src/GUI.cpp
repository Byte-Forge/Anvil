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
#include <GLFW/glfw3.h>
#include <spark/spark.hpp>
using namespace anvil;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_core(nullptr),m_window(window), m_frameTick(1)
{
	m_core = std::make_unique<spark::Core>(false);

	auto fonts = IO::ListFiles("ui/fonts/");
	auto defaultFont = fonts.front();

	for (auto font : fonts)
	{
		std::cout << font << std::endl;
		if(!m_core->AddFont(font, "ui/fonts/" + font))
			std::cout << "Failed to add font!"<< std::endl;
	}
	
	m_view = m_core->CreateView(800,600);
	auto element = std::make_shared<spark::Grid>();	
	auto label = std::make_shared<spark::ILabel>();
	label->SetText("0");
	label->SetFontSize(36.0f);
	label->SetFont(defaultFont);
	element->AddChildren(label);
	
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
	auto label = std::dynamic_pointer_cast<spark::ILabel>(*m_view->GetRoot()->GetChildren().begin());
	int fps = Core::GetCore()->GetFPS().GetFPS();
	label->SetText(std::to_string(fps));

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

