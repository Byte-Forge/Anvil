#include "BrowserClient.hpp"
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
	return false;
}
