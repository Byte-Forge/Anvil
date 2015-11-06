#include "Core.hpp"

using namespace hpse;

std::unique_ptr<Graphics> Core::m_graphics = nullptr;
std::unique_ptr<Script> Core::m_script = nullptr;
std::unique_ptr<GUI> Core::m_gui = nullptr;

Core::Core()
{
	#ifdef NDEBUG
	m_window.create(sf::VideoMode(800, 600),"hpse",sf::Style::Default, 	
		sf::ContextSettings(24, 8, 0, 4, 0, sf::ContextSettings::Core));
	#else
	m_window.create(sf::VideoMode(800, 600), "hpse", sf::Style::Default,
		sf::ContextSettings(24, 8, 0, 4, 0, sf::ContextSettings::Debug));
	#endif	

	m_graphics = std::make_unique<Graphics>();
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_script->LoadFile("./script/start.lua");
	m_gui->LoadURL("http://www.leemunroe.com/demos/css3-loading-bar");
	//m_gui->LoadFile("./ui/loading.html");
}

Core::~Core()
{

}

void Core::Run()
{
	sf::Event event;

	while (m_window.isOpen())
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
				m_window.close();
				break;
			case sf::Event::Resized:
				m_gui->Resize(event.size.width, event.size.height);
				break;
			}
		}
		m_graphics->Render();
		m_window.display();
	}
}