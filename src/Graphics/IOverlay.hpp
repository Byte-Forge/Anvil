#pragma once
#include <stdint.h>

namespace hpse
{
	class IOverlay
	{
	public:
		virtual void Resize(int width, int height) = 0;
		//data is expected to be 32 bit RGBA
		virtual void Update(int x, int y, int width, int height, uint8_t* data) = 0;
		virtual void Bind() = 0;
	};
}