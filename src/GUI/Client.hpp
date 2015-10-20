#pragma once
#include <include/cef_client.h>

namespace hpse
{
	class GuiClient : CefClient
	{
	public:
		IMPLEMENT_REFCOUNTING(GuiClient);
	};
}