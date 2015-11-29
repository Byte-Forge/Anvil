#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"
#include <iostream>

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
	url += IO::GetCwd();
	url += '/';
	url += file;
	std::replace(url.begin(), url.end(), '\\', '/');
	m_browser->GetMainFrame()->LoadURL(url);
}

void GUI::Resize(int width, int height)
{
	m_renderer->Resize(width, height);
	m_browser->GetHost()->WasResized();
}

void GUI::MouseMove(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
	CefMouseEvent event;
	event.x = x;
	event.y = y;

	m_browser->GetHost()->SendMouseMoveEvent(event, false);
}

void GUI::MouseLeft(bool isDown)
{
	CefMouseEvent event;
	event.x = m_mouseX;
	event.y = m_mouseY;

	bool mouseUp = !isDown;
	CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
	m_browser->GetHost()->SendMouseClickEvent(event, btnType, mouseUp, 1);
}

void GUI::KeyDown(sf::Event::KeyEvent &key)
{
	//TODO: translate SFML keycodes to native keycodes and pass them to them to CEF
}

