#include "GUI.hpp"
#include "Environment.hpp"
#include "include/cef_app.h"
using namespace hpse;


GUI::GUI()
{
	m_client = new BrowserClient();
	CefMainArgs args;
	CefSettings settings;
	CefInitialize(args, settings, nullptr, NULL);
	m_renderer = new RenderHandler();
	m_client = new BrowserClient();
}

GUI::~GUI()
{
	CefShutdown();
}

void GUI::Update()
{
	CefDoMessageLoopWork();
}

void GUI::LoadFile(const std::string& file)
{

}