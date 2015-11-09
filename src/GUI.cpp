#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"

using namespace hpse;


GUI::GUI(sf::Window& window)
{
	CefBrowserSettings settings;
	CefWindowInfo window_info;
	window_info.SetAsWindowless(window.getSystemHandle(), true);
	window_info.width = 800;
	window_info.height = 600;
	settings.windowless_frame_rate = 60;
	m_renderer = new RenderHandler();
	m_renderer->Resize(800, 600);
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

void GUI::LoadURL(const std::string& file)
{
	m_browser->GetMainFrame()->LoadURL(file);
}

void GUI::LoadFile(const std::string& file)
{
	std::string url = "file://";
	auto cwd = IO::GetCwd();
	url += IO::GetCwd();
	m_browser->GetMainFrame()->LoadURL(file);
}

void hpse::GUI::Resize(int width, int height)
{
	m_renderer->Resize(width, height);
	m_browser->GetHost()->WasResized();
}

