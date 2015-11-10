#include "RenderHandler.hpp"
#include "../Core.hpp"
#include <iostream>
using namespace hpse;

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
	PaintElementType type,
	const RectList &dirtyRects,
	const void* buffer,
	int width,
	int height)
{
	Core::GetGraphics()->UpdateGUI(width,height, static_cast<const uint8_t*>(buffer));
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
	rect = CefRect(0, 0, m_width, m_height);
	return true;
}