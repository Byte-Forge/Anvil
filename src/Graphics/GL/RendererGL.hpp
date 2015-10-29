#pragma once
#include "../IRenderer.hpp"

namespace hpse
{
	class RendererGL : public IRenderer
	{
	public:
		RendererGL();
		~RendererGL();

		void Clear();
		void Render();
		void Resize(int width, int height);

	private:

	};
}