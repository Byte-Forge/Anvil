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
	private:
		CefRefPtr<BrowserClient>	m_client;
		RenderHandler*				m_renderer;
		CefRefPtr<CefBrowser>		m_browser;
		CefSettings m_settings;
	};
}