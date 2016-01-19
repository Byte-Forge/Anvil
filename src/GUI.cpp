#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"
#include <iostream>
#include "Exception.hpp"
#include <Rocket/Debugger.h>
#include "Core.hpp"
using namespace hpse;

GUI::GUI(sf::Window& window) : m_context(nullptr), m_window(&window)
{
	Rocket::Core::SetSystemInterface(&m_system);
	Rocket::Core::SetRenderInterface(Core::GetCore()->GetGraphics()->GetRenderer()->GetRocketRenderer().get());
	if (!Rocket::Core::Initialise())
	{
		throw HpseException("Failed to initialise librocket", __FILE__, __LINE__);
	}

	m_context = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(window.getSize().x, window.getSize().y));
	Rocket::Debugger::Initialise(m_context);

}

GUI::~GUI()
{
	m_context->RemoveReference();
	Rocket::Core::Shutdown();
}

void GUI::Update()
{
	m_context->Update();
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
	
}

