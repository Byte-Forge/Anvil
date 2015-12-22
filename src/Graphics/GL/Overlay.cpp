#include "Overlay.hpp"

using namespace hpse;

GL::Overlay::Overlay() : m_handle(0)
{
	glGenTextures(1, &m_handle);
}

GL::Overlay::~Overlay()
{
	if (m_handle)
		glDeleteTextures(1, &m_handle);
}


void GL::Overlay::Resize(int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
}

void GL::Overlay::Update(int x, int y, int width, int height, uint8_t* data)
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
}

void GL::Overlay::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

