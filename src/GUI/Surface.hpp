#pragma once
#include <Awesomium/Surface.h>

namespace hpse
{
	class Surface : public Awesomium::Surface
	{
	public:
		void Paint(unsigned char* src_buffer,
			int src_row_span,
			const Awesomium::Rect& src_rect,
			const Awesomium::Rect& dest_rect);

		void Scroll(int dx,
			int dy,
			const Awesomium::Rect& clip_rect);
	};
	
}