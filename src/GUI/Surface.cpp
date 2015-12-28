#include "Surface.hpp"
#include "../Graphics.hpp"
#include "../Core.hpp"
#include "../Graphics/IOverlay.hpp"
using namespace hpse;

Surface::Surface(int width, int height)
{
	Core::GetCore()->GetGraphics()->GetRenderer()->GetOverlay()->Resize(width, height);
}

Surface::~Surface()
{

}

void Surface::Paint(unsigned char * src_buffer, int src_row_span, 
	const Awesomium::Rect & src_rect, const Awesomium::Rect & dest_rect)
{
	Core::GetCore()->GetGraphics()->GetRenderer()->GetOverlay()->Update(dest_rect.x, dest_rect.y, dest_rect.width, dest_rect.height, src_buffer);
}

void Surface::Scroll(int dx, int dy, const Awesomium::Rect & clip_rect)
{

}
