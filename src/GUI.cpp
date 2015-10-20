#include "GUI.hpp"
#include "Environment.hpp"
#include "include/cef_app.h"
using namespace hpse;


GUI::GUI()
{
	m_client = new GuiClient();
	
	CefInitialize(CefMainArgs(), m_settings, NULL,NULL);
}

GUI::~GUI()
{
	CefShutdown();
}

void GUI::Update()
{

}

void GUI::LoadFile(const std::string& file)
{

}