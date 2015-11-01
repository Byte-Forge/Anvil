#pragma once
#include <include/cef_client.h>
#include "RenderHandler.hpp"

namespace hpse
{
	class BrowserClient : public CefClient
	{
	public:
		BrowserClient(RenderHandler*);

		virtual CefRefPtr<CefRenderHandler> GetRenderHandler();
		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
			CefProcessId source_process,
			CefRefPtr<CefProcessMessage> message);
	private:
		CefRefPtr<CefRenderHandler> m_handler;
		IMPLEMENT_REFCOUNTING(BrowserClient);
	};
}