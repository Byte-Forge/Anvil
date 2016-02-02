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
using namespace hpse;

GUI::GUI(sf::Window& window) : m_context(nullptr), m_window(&window)
{
	Rocket::Core::SetSystemInterface(&m_system);
	Rocket::Core::SetRenderInterface(Core::GetCore()->GetGraphics()->GetRenderer().get());

	if (!Rocket::Core::Initialise())
	{
		throw HpseException("Failed to initialise librocket", __FILE__, __LINE__);
	}

	Rocket::Core::String font_names[4];
	auto fonts = IO::ListFiles("ui/fonts/");

	for (auto font : fonts)
	{
		if (!Rocket::Core::FontDatabase::LoadFontFace(Rocket::Core::String("ui/fonts/") + Rocket::Core::String(font.c_str())))
		{
			throw HpseException("Failed to load font: " + font, __FILE__, __LINE__);
		}
	}

	Rocket::Core::Lua::Interpreter::Initialise();
	Rocket::Controls::Lua::RegisterTypes(Rocket::Core::Lua::Interpreter::GetLuaState());

	m_script.Initialise(Rocket::Core::Lua::Interpreter::GetLuaState());
	m_context = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(window.getSize().x, window.getSize().y));
	Rocket::Debugger::Initialise(m_context);
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

	std::function<void(Rocket::Core::Element*)> updateElement = [&] (Rocket::Core::Element* element)
	{
		element->DispatchEvent("update", Rocket::Core::Dictionary(), false);
		for (int i = 0;i < element->GetNumChildren();++i)
		{
			auto* child = element->GetChild(i);
			updateElement(child);
		}
	};
	auto* root = m_context->GetRootElement();

	updateElement(root);
}


void GUI::Render()
{
	m_context->Render();
}


void GUI::LoadURL(const std::string& file)
{
	
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

void GUI::MouseMove(int x, int y)
{
	m_context->ProcessMouseMove(x, y, m_system.GetKeyModifiers(m_window));
}

void GUI::MousePressed(int key)
{
	m_context->ProcessMouseButtonDown(key, m_system.GetKeyModifiers(m_window));
}

void GUI::MouseReleased(int key)
{
	m_context->ProcessMouseButtonUp(key, m_system.GetKeyModifiers(m_window));
}

void GUI::KeyDown(sf::Event::KeyEvent &key)
{
	m_context->ProcessKeyDown(m_system.TranslateKey(key.code),
		m_system.GetKeyModifiers(m_window));
}

void GUI::KeyReleased(sf::Event::KeyEvent & key)
{
	if (key.code == sf::Keyboard::F11)
	{
		Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
	};

	m_context->ProcessKeyUp(m_system.TranslateKey(key.code),
		m_system.GetKeyModifiers(m_window));
}

