#pragma once

namespace hpse
{
	class IRenderable
	{
	public:
		virtual void Render() = 0;
		virtual void Update() = 0;
	};
}