#include "GUI.hpp"
#include "Environment.hpp"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace hpse;


GUI::GUI(sf::Window& window)
{
	CefBrowserSettings settings;
	CefWindowInfo window_info;
	window_info.SetAsWindowless(window.getSystemHandle(), true);
	window_info.width = 800;
	window_info.height = 600;
	window_info.transparent_painting_enabled = true;
	settings.windowless_frame_rate = 60;

	m_renderer = new RenderHandler();
	m_client = new BrowserClient(m_renderer);
	m_browser = CefBrowserHost::CreateBrowserSync(window_info, m_client.get(), "", settings, nullptr);
}

GUI::~GUI()
{
	m_browser->GetHost()->CloseBrowser(false);
}

void GUI::Update()
{
	CefDoMessageLoopWork();
}

void GUI::LoadFile(const std::string& file)
{
	m_browser->GetMainFrame()->LoadURL(file);
}

void hpse::GUI::Resize(int width, int height)
{
	m_renderer->Resize(width, height);
	m_browser->GetHost()->WasResized();
}

