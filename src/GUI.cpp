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
#include <Rocket/Debugger.h>
#include <Rocket/Core/Lua/Interpreter.h>
#include <Rocket/Controls/Lua/Controls.h>
#include <functional>
#include "Core.hpp"
#include "Util/Platform.hpp"
#include "Graphics.hpp"
using namespace anvil;

const int GUI::UPDATES_PER_SECOND = 30;

GUI::GUI(GLFWwindow* window) : m_context(nullptr), m_window(window), m_frameTick(1)
{
	Rocket::Core::SetSystemInterface(&m_system);
	Rocket::Core::SetRenderInterface(Core::GetCore()->GetGraphics()->GetRenderer().get());

	if (!Rocket::Core::Initialise())
	{
		throw AnvilException("Failed to initialise librocket", __FILE__, __LINE__);
	}

	Rocket::Core::String font_names[4];
	auto fonts = IO::ListFiles("ui/fonts/");

	for (auto font : fonts)
	{
		if (!Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String("ui/fonts/") + Rocket::Core::String(font.c_str())))
		{
			throw AnvilException("Failed to load font: " + font, __FILE__, __LINE__);
		}
	}

	Rocket::Core::Lua::Interpreter::Initialise();
	Rocket::Controls::Lua::RegisterTypes(Rocket::Core::Lua::Interpreter::GetLuaState());

	m_script.Initialise(Rocket::Core::Lua::Interpreter::GetLuaState());
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	m_context = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(width, height));
	Rocket::Debugger::Initialise(m_context);

	m_updateInterval = (1.0f / UPDATES_PER_SECOND)*1e6;

	m_accumulatedTime = 0;
}

GUI::~GUI()
{
	Rocket::Core::Lua::Interpreter::Shutdown();
	m_context->RemoveReference();
	Rocket::Core::Shutdown();
}

void GUI::Update()
{
	m_context->Update();
	Rocket::Core::Dictionary params;

	std::function<void(Rocket::Core::Element*)> updateElement = [&] (Rocket::Core::Element* element)
	{
		element->DispatchEvent("update", params, false);
		for (int i = 0;i < element->GetNumChildren();++i)
		{
			auto* child = element->GetChild(i);
			updateElement(child);
		}
	};
	auto* root = m_context->GetRootElement();

	m_accumulatedTime += Core::GetCore()->GetTimer().GetElapsedTime();
	auto updates = m_accumulatedTime / m_updateInterval;

	for (int i = 0;i < updates;++i)
	{
		params.Set<int>("frame", m_frameTick);
		updateElement(root);	
		m_accumulatedTime -= m_updateInterval;
		++m_frameTick;
		if (m_frameTick > 30)
		{
			m_frameTick -= 30;
		}
	}

	
}

void GUI::Render()
{
	m_context->Render();
}

void GUI::LoadFile(const std::string& file)
{
	auto* document = m_context->LoadDocument(file.c_str());
	if (document)
	{	
		document->Show();
		document->RemoveReference();
		std::cout << "Document " << file << " is loaded" << std::endl;
	}
	else
	{
		std::cout << "Document " << file << " is NULL" << std::endl;
	}
}

void GUI::Resize(int width, int height)
{
	m_context->SetDimensions(Rocket::Core::Vector2i(width, height));
}

void GUI::MouseMove(int x, int y, int mods)
{
	m_context->ProcessMouseMove(x, y, m_system.GetKeyModifiers(mods));
}

void GUI::MousePressed(int key, int mods)
{
	m_context->ProcessMouseButtonDown(key, m_system.GetKeyModifiers(mods));
}

void GUI::MouseReleased(int key, int mods)
{
	m_context->ProcessMouseButtonUp(key, m_system.GetKeyModifiers(mods));
}

void GUI::KeyDown(int key, int mods)
{
	m_context->ProcessKeyDown(m_system.TranslateKey(key),m_system.GetKeyModifiers(mods));
}

void GUI::KeyReleased(int key, int mods)
{
	if (key == GLFW_KEY_F11)
	{
		Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
	};

	m_context->ProcessKeyUp(m_system.TranslateKey(key), m_system.GetKeyModifiers(mods));
}

