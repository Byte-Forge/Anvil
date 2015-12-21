#include "SurfaceFactory.hpp"
#include "Surface.hpp"
#include <iostream>
using namespace hpse;

Awesomium::Surface * SurfaceFactory::CreateSurface(Awesomium::WebView * view, int width, int height)
{
	return new Surface(width,height);
}

void SurfaceFactory::DestroySurface(Awesomium::Surface * surface)
{
	if (surface)
		delete surface;
}
