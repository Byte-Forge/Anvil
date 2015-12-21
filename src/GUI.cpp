#include "GUI.hpp"
#include "Environment.hpp"
#include "./Util/Platform.hpp"
#include <iostream>
#include <Awesomium/STLHelpers.h>
#include "./GUI/Surface.hpp"

using namespace hpse;
using namespace Awesomium;

GUI::GUI(sf::Window& window) : m_core(nullptr), m_view(nullptr), m_factory(nullptr)
{
	m_core = WebCore::Initialize(WebConfig());
	m_factory = new SurfaceFactory();
	m_core->set_surface_factory(m_factory);
	m_view = m_core->CreateWebView(window.getSize().x, window.getSize().y);
	m_view->Focus();
}

GUI::~GUI()
{
	if (m_factory)
		delete m_factory;

	WebCore::Shutdown();
}

void GUI::Update()
{
	m_core->Update();
	auto surface = static_cast<hpse::Surface*>(m_view->surface());
}

void GUI::LoadURL(const std::string& file)
{
	WebURL url(WSLit(file.c_str()));
	if (!url.IsValid())
	{
		std::cout << "Invalid URL" << std::endl;
		return;
	}
	m_view->LoadURL(url);
}

void GUI::LoadFile(const std::string& file)
{
	std::string path = "file://";
	path += IO::GetCwd();
	path += '/';
	path += file;
	std::replace(path.begin(), path.end(), '\\', '/');
	WebURL url = WebURL(WSLit(path.c_str()));
	if(!url.IsValid())
	{
		std::cout << "Invalid URL" << std::endl;
		return;
	}
	m_view->LoadURL(url);
}

void GUI::Resize(int width, int height)
{
	m_view->Resize(width, height);
}

void GUI::MouseMove(int x, int y)
{
	m_view->InjectMouseMove(x, y);
}

void GUI::MouseLeft(bool isDown)
{
	if(isDown)
		m_view->InjectMouseDown(Awesomium::MouseButton::kMouseButton_Left);
	else
		m_view->InjectMouseUp(Awesomium::MouseButton::kMouseButton_Left);
}

void GUI::KeyDown(sf::Event::KeyEvent &key)
{
	//TODO: translate SFML keycodes to native keycodes and pass them to them to CEF
}

