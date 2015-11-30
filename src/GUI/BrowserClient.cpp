#include "BrowserClient.hpp"
#include "../Core.hpp"
#include <iostream>
using namespace hpse;

BrowserClient::BrowserClient(RenderHandler* handler) : m_handler(handler)
{
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler()
{
	return m_handler;
}

bool BrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
											 CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	const std::string& message_name = message->GetName();
	if(message_name=="quit")
	{
		std::cout << "Quit" << std::endl;
		Core::Quit();
	}

	return false;
}
