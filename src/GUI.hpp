#pragma once
#include <memory>
#include <string>
#include <include/cef_client.h>
#include <include/cef_browser.h>
#include <include/cef_app.h>
#include <SFML/Window.hpp>
#include "./GUI/BrowserClient.hpp"
#include "./GUI/RenderHandler.hpp"

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
		CefRefPtr<BrowserClient>	m_client;
		RenderHandler*				m_renderer;
		CefRefPtr<CefBrowser>		m_browser;
		CefSettings m_settings;
		int m_mouseX, m_mouseY;
	};
}