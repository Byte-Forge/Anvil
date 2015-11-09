#pragma once
#include "ITexture.hpp"
#include "IShader.hpp"
#include <glm/glm.hpp>

namespace hpse
{
	class IRenderer
	{
	public:
		virtual void Clear() = 0;
		virtual void Render(glm::mat4& ortho) = 0;
		inline void UpdateGUI(int width,int height,const uint8_t* data)
		{
			m_overlay->Update(width,height,data);
		}
		virtual void Resize(int width,int height) = 0;
	protected:
		std::unique_ptr<ITexture> m_overlay;
		std::unique_ptr<IShader> m_guiShader;
	};
}