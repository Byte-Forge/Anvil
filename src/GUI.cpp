#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"
#include <iostream>
#include "Exception.hpp"
#include <Rocket/Debugger.h>
#include "Core.hpp"
using namespace hpse;

GUI::GUI(sf::Window& window) : m_context(nullptr)
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
	//m_context->Update();
}


void GUI::Render()
{
	//m_context->Render();
}


void GUI::LoadURL(const std::string& file)
{
	
}

void GUI::LoadFile(const std::string& file)
{
	
}

void GUI::Resize(int width, int height)
{
	
}

void GUI::MouseMove(int x, int y)
{
	
}

void GUI::MouseLeft(bool isDown)
{
	
}

void GUI::KeyDown(sf::Event::KeyEvent &key)
{
	
}

