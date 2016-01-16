#pragma once
#include <memory>
#include <string>
#include <SFML/Window.hpp>
#include <Rocket/Core.h>

namespace hpse
{

	class GUI
	{
	public:
		GUI(sf::Window& window);
		~GUI();

		void Update();
		void LoadURL(const std::string& url);
		void LoadFile(const std::string& file);
		void Resize(int width, int height);

		//Events
		void MouseMove(int x, int y);
		void MouseLeft(bool isDown);
		void KeyDown(sf::Event::KeyEvent& key);
	private:
		int m_mouseX, m_mouseY;
	
	};
}