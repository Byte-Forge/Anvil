/*
************************************
* Copyright (C) 2016 ByteForge
* FrameBufferGL.cpp
************************************
*/

#include "FrameBufferGL.hpp"
#include "TextureGL.hpp"

using namespace anvil;

GL::FrameBuffer::FrameBuffer()
{

}

GL::FrameBuffer::FrameBuffer(glm::vec2 size) : m_size(size)
{
	glGenFramebuffers(1, &m_handle);
}

GL::FrameBuffer::~FrameBuffer()
{
	if (m_handle)
	{
		glDeleteFramebuffers(1, &m_handle);
		m_handle = 0;
	}
}

void GL::FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	glViewport(0, 0, m_size.x, m_size.y);
}

bool GL::FrameBuffer::Valid()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;
	return true;
}

void GL::FrameBuffer::AttachTexture()
{
	m_texture = std::make_shared<GL::Texture>();
	m_texture->Create(m_size.x, m_size.y);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture->GetHandle(), 0);
}