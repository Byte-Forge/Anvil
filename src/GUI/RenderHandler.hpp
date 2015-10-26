#pragma once
#include <include/cef_render_handler.h>

namespace hpse
{
	class RenderHandler : public CefRenderHandler
	{
	public:
		inline void Resize(int w,int h)
		{
			m_width = w;
			m_height = h;
		}

		void OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList &dirtyRects,
			const void* buffer,
			int width,
			int height);

		bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
	private:
		IMPLEMENT_REFCOUNTING(RenderHandler);
		int m_width;
		int m_height;
	};
}