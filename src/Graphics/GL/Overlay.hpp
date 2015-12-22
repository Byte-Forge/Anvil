#pragma once
#include "../IOverlay.hpp"
#include "./flextGL.h"
namespace hpse
{
	namespace GL
	{
		class Overlay : public IOverlay
		{
		public:
			Overlay();
			~Overlay();

			void Resize(int width, int height);
			void Update(int x, int y, int width, int height, uint8_t* data);
			void Bind();
		private:
			GLuint m_handle;
		};
	}
}