#include "RenderHandler.hpp"

using namespace hpse;

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList &dirtyRects,
	const void* buffer,
	int width,
	int height)
{
	int a = 0;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
	return true;
}