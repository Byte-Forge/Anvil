#pragma once
#include <include/cef_render_handler.h>

namespace hpse
{
	class RenderHandler : CefRenderHandler
	{
	public:
		void OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList &dirtyRects,
			const void* buffer,
			int width,
			int height);

		bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
	private:
		IMPLEMENT_REFCOUNTING(RenderHandler);
	};
}