/*
************************************
* Copyright (C) 2016 ByteForge
* Core.cpp
************************************
*/

#include "Core.hpp" 
#include "Math/Collision.hpp"
#include "Util/FPS.hpp"
#include <iostream>

using namespace anvil;

Core* Core::m_instance = nullptr;

Core::Core()
{
	m_instance = this;
	
	m_window.create(sf::VideoMode(800, 600), "anvil engine", sf::Style::Default,
		sf::ContextSettings(24, 8, 0, 4, 0, sf::ContextSettings::Core));

	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>();
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_resources = std::make_unique<ResourceHandler>();
	m_camera = std::make_unique<Camera>();

	m_script->LoadFile("start.lua");

	m_map = std::make_unique<Map>();
}

Core::~Core()
{
	if(m_window.isOpen())
		m_window.close();
}

void Core::Run()
{
	sf::Event event;

	//mouse variables
	int x_old = 0; 
	int y_old = 0; 
	int delta_x = 0;
	int delta_y = 0;
	int delta_wheel = 0;
	m_running = true;

	while (m_window.isOpen() && m_running)
	{
		m_timer.Update();
		m_fps.Update();
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
				m_mouseInputs[sf::Event::MouseMoved] = 1;
				break;

			case sf::Event::MouseButtonPressed:
				m_gui->MousePressed(event.mouseButton.button);
				m_mouseInputs[event.mouseButton.button] = 1;
				break;

			case sf::Event::MouseButtonReleased:
				m_gui->MouseReleased(event.mouseButton.button);
				m_mouseInputs[event.mouseButton.button] = -1; //set it to just released
				break;

			case sf::Event::MouseWheelMoved:
				delta_wheel = event.mouseWheel.delta;
				m_mouseInputs[sf::Event::MouseWheelMoved] = 1;
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					Quit();
				m_keyInputs[event.key.code] = 1;
				m_gui->KeyDown(event.key);
				break;

			case sf::Event::KeyReleased:
				m_keyInputs[event.key.code] = -1;
				m_gui->KeyReleased(event.key);
				break;
			}
		}

		if (m_keyInputs[sf::Keyboard::W] == 1 || m_keyInputs[sf::Keyboard::Up] == 1)
			m_camera->Move(FOREWARD);
		if (m_keyInputs[sf::Keyboard::S] == 1 || m_keyInputs[sf::Keyboard::Down] == 1)
			m_camera->Move(BACK);
		if (m_keyInputs[sf::Keyboard::A] == 1 || m_keyInputs[sf::Keyboard::Left] == 1)
			m_camera->Move(LEFT);
		if (m_keyInputs[sf::Keyboard::D] == 1 || m_keyInputs[sf::Keyboard::Right] == 1)
			m_camera->Move(RIGHT);
		if (m_keyInputs[sf::Keyboard::PageUp] == 1 || ((m_mouseInputs[sf::Event::MouseWheelMoved] == 1) && delta_wheel < 0))
			m_camera->Zoom(ZOOM_OUT);
		if (m_keyInputs[sf::Keyboard::PageDown] == 1 || ((m_mouseInputs[sf::Event::MouseWheelMoved] == 1) && delta_wheel > 0))
			m_camera->Zoom(ZOOM_IN);
		if (m_keyInputs[sf::Keyboard::Q] == 1)
			m_camera->Rotate(LEFT);
		if (m_keyInputs[sf::Keyboard::E] == 1)
			m_camera->Rotate(RIGHT);

		if (m_keyInputs[sf::Keyboard::F1] == -1)
		{
			this->GetGraphics()->GetRenderer()->ToggleWireframeMode();
			m_keyInputs[sf::Keyboard::F1] = 0;
		}

		if (m_keyInputs[sf::Keyboard::F2] == -1)
		{
			this->GetGraphics()->GetRenderer()->ToggleNormalsMode();
			m_keyInputs[sf::Keyboard::F2] = 0;
		}

		if (m_keyInputs[sf::Keyboard::F3] == -1)
		{
			this->GetGraphics()->GetRenderer()->IncreaseTessellation();
			m_keyInputs[sf::Keyboard::F3] = 0;
		}

		if (m_keyInputs[sf::Keyboard::F4] == -1)
		{
			this->GetGraphics()->GetRenderer()->DecreaseTessellation();
			m_keyInputs[sf::Keyboard::F4] = 0;
		}

		if (m_mouseInputs[sf::Event::MouseMoved] == 1)
		{
			if (m_mouseInputs[sf::Mouse::Right] == 1)
			{
				glm::vec3 dir = { delta_x / 4.0, 0.0, delta_y / 4.0 };
				m_camera->Move(dir);
			}
			else if (m_mouseInputs[sf::Mouse::Middle] == 1)
			{
				m_camera->Rotate(delta_x / 100.0f);
			}
			m_mouseInputs[sf::Event::MouseMoved] = 0;
		}

		if (m_mouseInputs[sf::Mouse::Left] == -1)
		{
			glm::vec2 mousePos = { x_old, y_old };
			glm::vec3 mouseWorld;
			if (m_map->GetTerrain()->GetMousePositionInWorldSpace(mousePos, mouseWorld))
			{
				m_map->GetTerrain()->SetMaterial(mouseWorld, 20.0f, 0);
				m_map->GetTerrain()->SetHeight(mouseWorld, 20.0f, 5.0f);
				std::cout << "set material" << std::endl;
			}
			m_mouseInputs[sf::Mouse::Left] = 0;
		}

		m_mouseInputs[sf::Event::MouseWheelMoved] = 0;

		m_graphics->Render();
		m_gui->Render();
		m_window.display();
	}
}