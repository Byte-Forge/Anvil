//
// Created by stephan on 27.10.15.
//

#include "flextGL.h"
#include "Texture.hpp"
#include <string>

using namespace hpse;

//is used to create a simple texture for the gui
GL::Texture::Texture()
{
	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GL::Texture::Texture(GLuint handle)
{
	m_handle = handle;
}

GL::Texture::~Texture()
{
    //glDeleteTextures(1, &m_handle);
}

void GL::Texture::Update(int width, int height, const uint8_t *data)
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
}

void GL::Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_handle);
}


