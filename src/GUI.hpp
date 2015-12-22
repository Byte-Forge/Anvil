#pragma once
#include <memory>
#include <string>
#include <SFML/Window.hpp>
#include <Awesomium/WebCore.h>
#include "./GUI/SurfaceFactory.hpp"
#include "./GUI/MethodHandler.hpp"

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
		Awesomium::WebCore* m_core;
		Awesomium::WebView* m_view;
		Awesomium::JSObject m_jsGlobal;
		SurfaceFactory* m_factory;
		MethodHandler* m_jsHandler;
		int m_mouseX, m_mouseY;
	};
}