#pragma once
#include <include/cef_client.h>

namespace hpse
{
	class BrowserClient : CefClient
	{
	private:
		IMPLEMENT_REFCOUNTING(BrowserClient);
	};
}