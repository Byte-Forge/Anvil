#pragma once
#include "IShader.hpp"
#include "../Core/IResource.hpp"
#include "ITexture.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <memory>


namespace hpse
{
	class IRenderable
	{
	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}