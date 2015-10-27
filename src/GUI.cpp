#include "GUI.hpp"
#include "Environment.hpp"
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
using namespace hpse;


GUI::GUI()
{
	CefBrowserSettings settings;
	CefWindowInfo window_info;
	window_info.windowless_rendering_enabled = true;
	window_info.transparent_painting_enabled = true;
	window_info.width = 800;
	window_info.height = 600;
	m_renderer = new RenderHandler();
	m_client = new BrowserClient(m_renderer);
	m_browser = CefBrowserHost::CreateBrowserSync(window_info, m_client.get(), "./ui/loading.html", settings, nullptr);
	m_renderer->Resize(800, 600);
	m_browser->GetHost()->WasResized();
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

void hpse::GUI::Resize(int width, int height)
{
	m_renderer->Resize(width, height);
	m_browser->GetHost()->WasResized();
}

