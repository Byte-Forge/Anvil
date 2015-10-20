#pragma once
#include <memory>
#include <string>
#include <include/cef_client.h>
#include <include/cef_browser.h>
#include "./GUI/Client.hpp"
namespace hpse
{
	class GUI
	{
	public:
		GUI();
		~GUI();

		void Update();
		void LoadFile(const std::string& file);
	private:
		CefRefPtr<GuiClient> m_client;
		CefSettings m_settings;
	};
}