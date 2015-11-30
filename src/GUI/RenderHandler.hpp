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

		virtual void OnPaint(CefRefPtr<CefBrowser> browser,
			PaintElementType type,
			const RectList &dirtyRects,
			const void* buffer,
			int width,
			int height) OVERRIDE;

		bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
	private:
		IMPLEMENT_REFCOUNTING(RenderHandler);
		int m_width;
		int m_height;
	};
}