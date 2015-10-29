#pragma once
#include "ITexture.hpp"
#include "IShader.hpp"

namespace hpse
{
	class IRenderer
	{
	public:
		virtual void Clear() = 0;
		virtual void Render() = 0;
		inline void UpdateGUI(int width,int height,const uint8_t* data)
		{
			m_overlay->Update(width,height,data);
		}
	protected:
		std::unique_ptr<ITexture> m_overlay;
		std::unique_ptr<IShader> m_guiShader;
	};
}