#pragma once
#include <Awesomium/Surface.h>

namespace hpse
{
	class Surface : public Awesomium::Surface
	{
	public:
		Surface(int width,int height);
		~Surface();

		void Paint(unsigned char* src_buffer,
			int src_row_span,
			const Awesomium::Rect& src_rect,
			const Awesomium::Rect& dest_rect);

		void Scroll(int dx,
			int dy,
			const Awesomium::Rect& clip_rect);
	};
	
}