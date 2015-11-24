#include "Core.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/GL/Texture.hpp"

using namespace hpse;

std::unique_ptr<Graphics> Core::m_graphics = nullptr;
std::unique_ptr<Script> Core::m_script = nullptr;
std::unique_ptr<GUI> Core::m_gui = nullptr;
std::unique_ptr<Audio> Core::m_audio = nullptr;
bool Core::m_running = true;

Core::Core()
{
	#ifdef NDEBUG
	m_window.create(sf::VideoMode(800, 600),"hpse",sf::Style::Default, 	
		sf::ContextSettings(24, 8, 0, 4, 0, sf::ContextSettings::Core));
	#else
	m_window.create(sf::VideoMode(800, 600), "hpse", sf::Style::Default,
		sf::ContextSettings(24, 8, 0, 4, 5, sf::ContextSettings::Debug));
	#endif	

	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>();
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_script->LoadFile("./script/start.lua");

	ResourceHandler::instance()->GetResource("gumaarms_skn", w4d);
	ResourceHandler::instance()->GetResource("gumanatarms", texture);
}

Core::~Core()
{
	if(m_window.isOpen())
		m_window.close();
}

void Core::Run()
{
	sf::Event event;

	while (m_window.isOpen() && m_running)
	{
		m_graphics->Clear();
		m_gui->Update();
		m_script->Update();

		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			//close the window
			case sf::Event::Closed:
				Quit();
				break;
			case sf::Event::Resized:
				m_graphics->Resize(event.size.width, event.size.height);
				m_gui->Resize(event.size.width, event.size.height);
				break;
			case sf::Event::MouseMoved:
				m_gui->MouseMove(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_gui->MouseLeft(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_gui->MouseLeft(false);
				}
				break;
			case sf::Event::KeyPressed:
				if(event.key.code==sf::Keyboard::Escape)
					Quit();
				m_gui->KeyDown(event.key);
				break;
			}
		}
		m_graphics->Render();
		m_window.display();
	}
}