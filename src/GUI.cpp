#include "GUI.hpp"
#include "Environment.hpp"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
using namespace hpse;


GUI::GUI()
{
	m_client = new BrowserClient();
	#ifdef _WIN32
	CefMainArgs args(GetModuleHandle(NULL));
	#else
	CefMainArgs args(Environment::Argc, Environment::Argv);
	#endif

	CefWindowInfo window_info;
	window_info.windowless_rendering_enabled = true;
	
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

