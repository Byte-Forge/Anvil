#include "Core.hpp" 
#include "Graphics/GL/Texture.hpp"
#include <iostream>

using namespace hpse;

std::unique_ptr<ResourceHandler> Core::m_resources = nullptr;
std::unique_ptr<Graphics> Core::m_graphics = nullptr;
std::unique_ptr<Script> Core::m_script = nullptr;
std::unique_ptr<GUI> Core::m_gui = nullptr;
std::unique_ptr<Audio> Core::m_audio = nullptr;
std::unique_ptr<Map> Core::m_map = nullptr;
std::unique_ptr<Camera> Core::m_camera = nullptr;

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
	m_resources = std::make_unique<ResourceHandler>();
	m_map = std::make_unique<Map>();
	m_camera = std::make_unique<Camera>();

	m_script->LoadFile("./script/start.lua");
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
		m_camera->Update();

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
				else if (event.mouseButton.button == sf::Mouse::Middle)
				{
					//TODO:test if the mouse is also moved and rotate left or right if true
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_gui->MouseLeft(false);
				}
				break;
			case sf::Event::MouseWheelMoved:
				if (event.mouseWheel.delta > 0)
					m_camera->Zoom(ZOOM_IN);
				else
					m_camera->Zoom(ZOOM_OUT);
				break;
			case sf::Event::KeyPressed:
				int code = event.key.code;
				if(event.key.code==sf::Keyboard::Escape)
					Quit();

				if (code == 73 || code == 22) //foreward
					m_camera->Move(FOREWARD); 
				if (code == 74 || code == 18) //back
					m_camera->Move(BACK);
				if (code == 71 || code == 0) // left
					m_camera->Move(LEFT);
				if (code == 72 || code == 3) // right
					m_camera->Move(RIGHT);
				if (code == 61 || code == -1) // up
					m_camera->Zoom(ZOOM_OUT);
				if (code == 62 || code == 38) // down
					m_camera->Zoom(ZOOM_IN);
				if (code == 49 || code == 16) // rotate left
					m_camera->Rotate(LEFT);
				if (code == 50 || code == 4) // rotate right
					m_camera->Rotate(RIGHT);

				
				m_gui->KeyDown(event.key);
				
				//std::cout << event.key.code << std::endl;
				break;
			}
		}
		m_map->m_terrain->Render();
		//m_graphics->Render();
		//create a vector of shared_ptr of all entities in core and iterate and render them here?

		m_window.display();
	}
}