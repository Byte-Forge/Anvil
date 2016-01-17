#include "Core.hpp" 
#include "Math\Collision.hpp"
#include <iostream>

using namespace hpse;

Core* Core::m_instance = nullptr;

Core::Core()
{
	m_instance = this;

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
	m_camera = std::make_unique<Camera>();

	m_script->LoadFile("start.lua");

	m_map = std::make_unique<Map>();

	//init user inputs
	m_inputs.insert({ "FOREWARD", false });
	m_inputs.insert({ "BACK", false });
	m_inputs.insert({ "LEFT", false });
	m_inputs.insert({ "RIGHT", false });

	m_inputs.insert({ "ZOOM_IN", false });
	m_inputs.insert({ "ZOOM_OUT", false });
	m_inputs.insert({ "ROTATE_LEFT", false });
	m_inputs.insert({ "ROTATE_RIGHT", false });

	m_inputs.insert({ "MOUSE_BUTTON_LEFT", false });
	m_inputs.insert({ "MOUSE_BUTTON_LEFT_RELEASED", false });
	m_inputs.insert({ "MOUSE_BUTTON_MIDDLE", false });
	m_inputs.insert({ "MOUSE_BUTTON_RIGHT", false });

	m_inputs.insert({ "MOUSE_MOVED", false });
	m_inputs.insert({ "MOUSE_WHEEL_MOVED", false });
}

Core::~Core()
{
	if(m_window.isOpen())
		m_window.close();
}

void Core::Run()
{
	sf::Event event;
	m_window.setFramerateLimit(60);

	//mouse variables
	int x_old = 0; 
	int y_old = 0; 
	int delta_x = 0;
	int delta_y = 0;
	int delta_wheel = 0;

	while (m_window.isOpen() && m_running)
	{
		m_graphics->Clear();
		m_gui->Update();
		m_script->Update();
		m_camera->Update();

		/*
		*user input is handled this way because of better performance 
		*and the benefit of processing multiple events at the same time
		*/
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
				int code;
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
				delta_x = event.mouseMove.x - x_old;
				delta_y = event.mouseMove.y - y_old;
				x_old = event.mouseMove.x;
				y_old = event.mouseMove.y;
				m_inputs["MOUSE_MOVED"] = true;
				break;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_gui->MouseLeft(true);
					m_inputs["MOUSE_BUTTON_LEFT"] = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
					m_inputs["MOUSE_BUTTON_MIDDLE"] = true;
				else if (event.mouseButton.button == sf::Mouse::Right)
					m_inputs["MOUSE_BUTTON_RIGHT"] = true;
				break;

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					m_gui->MouseLeft(false);
					m_inputs["MOUSE_BUTTON_LEFT"] = false;
					m_inputs["MOUSE_BUTTON_LEFT_RELEASED"] = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Middle)
					m_inputs["MOUSE_BUTTON_MIDDLE"] = false;
				else if (event.mouseButton.button == sf::Mouse::Right)
					m_inputs["MOUSE_BUTTON_RIGHT"] = false;
				break;

			//this should be handled like the other inputs
			case sf::Event::MouseWheelMoved:
				delta_wheel = event.mouseWheel.delta;
				m_inputs["MOUSE_WHEEL_MOVED"] = true;
				break;

			case sf::Event::KeyPressed:
				code = event.key.code;
				if(event.key.code==sf::Keyboard::Escape)
					Quit();
				if (code == sf::Keyboard::W || code == sf::Keyboard::Up) 
					m_inputs["FOREWARD"] = true;
				else if (code == sf::Keyboard::S || code == sf::Keyboard::Down)
					m_inputs["BACK"] = true;
				else if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
					m_inputs["LEFT"] = true;
				else if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
					m_inputs["RIGHT"] = true;
				else if (code == sf::Keyboard::PageUp)
					m_inputs["ZOOM_OUT"] = true;
				else if (code == sf::Keyboard::PageDown)
					m_inputs["ZOOM_IN"] = true;
				else if (code == sf::Keyboard::Q || code == sf::Keyboard::Comma)
					m_inputs["ROTATE_LEFT"] = true;
				else if (code == sf::Keyboard::E || code == sf::Keyboard::Period)
					m_inputs["ROTATE_RIGHT"] = true;
				break;

			case sf::Event::KeyReleased:
				code = event.key.code;
				if (code == sf::Keyboard::W || code == sf::Keyboard::Up)
					m_inputs["FOREWARD"] = false;
				else if (code == sf::Keyboard::S || code == sf::Keyboard::Down)
					m_inputs["BACK"] = false;
				else if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
					m_inputs["LEFT"] = false;
				else if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
					m_inputs["RIGHT"] = false;
				else if (code == sf::Keyboard::PageUp)
					m_inputs["ZOOM_OUT"] = false;
				else if (code == sf::Keyboard::PageDown)
					m_inputs["ZOOM_IN"] = false;
				else if (code == sf::Keyboard::Q || code == sf::Keyboard::Comma)
					m_inputs["ROTATE_LEFT"] = false;
				else if (code == sf::Keyboard::E || code == sf::Keyboard::Period)
					m_inputs["ROTATE_RIGHT"] = false;
				break;
			}
		}

		if (m_inputs["FOREWARD"])
			m_camera->Move(FOREWARD);
		if (m_inputs["BACK"])
			m_camera->Move(BACK);
		if (m_inputs["LEFT"])
			m_camera->Move(LEFT);
		if (m_inputs["RIGHT"])
			m_camera->Move(RIGHT);
		if (m_inputs["ZOOM_OUT"])
			m_camera->Zoom(ZOOM_OUT);
		if (m_inputs["ZOOM_IN"])
			m_camera->Zoom(ZOOM_IN);
		if (m_inputs["ROTATE_LEFT"])
			m_camera->Rotate(LEFT);
		if (m_inputs["ROTATE_RIGHT"])
			m_camera->Rotate(RIGHT);

		if (m_inputs["MOUSE_WHEEL_MOVED"])
		{
			if (delta_wheel > 0)
				m_camera->Zoom(ZOOM_IN);
			else 
				m_camera->Zoom(ZOOM_OUT);
			m_inputs["MOUSE_WHEEL_MOVED"] = false;
		}

		if (m_inputs["MOUSE_MOVED"])
		{
			if (m_inputs["MOUSE_BUTTON_RIGHT"])
			{
				glm::vec3 dir = { delta_x / 4.0, 0.0, delta_y / 4.0 };
				m_camera->Move(dir);
			}
			else if (m_inputs["MOUSE_BUTTON_MIDDLE"])
			{
				m_camera->Rotate(delta_x / 100.0f);
			}
			m_inputs["MOUSE_MOVED"] = false;
		}

		if (m_inputs["MOUSE_BUTTON_LEFT_RELEASED"])
		{
			glm::vec2 mousePos = { x_old, y_old };
			glm::vec3 mouseWorld;
			if (m_map->GetTerrain()->GetMousePositionInWorldSpace(mousePos, mouseWorld))
			{
				m_map->GetTerrain()->SetTerrainHeight(mouseWorld, 15.0f, 20.0f);
			}
			m_inputs["MOUSE_BUTTON_LEFT_RELEASED"] = false;
		}

		m_graphics->Render();

		m_window.display();
	}
}