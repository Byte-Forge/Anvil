#pragma once
#include "IShader.hpp"

namespace hpse
{
	class IRenderable
	{
	public:
		virtual void Render(ShaderMode mode) = 0;
		virtual void Update() = 0;
	};
}