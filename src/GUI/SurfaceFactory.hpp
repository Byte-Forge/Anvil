#pragma once
#include <Awesomium/Surface.h>

namespace hpse
{
	class SurfaceFactory : public Awesomium::SurfaceFactory
	{
	public:
		Awesomium::Surface* CreateSurface(Awesomium::WebView* view,
			int width,
			int height);

		void DestroySurface(Awesomium::Surface* surface);
	};
	
}