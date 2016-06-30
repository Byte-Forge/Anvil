/*
************************************
* Copyright (C) 2016 ByteForge
* FrameBufferGL.cpp
************************************
*/

#include "FrameBufferGL.hpp"
#include "TextureGL.hpp"
#include "../../Exception.hpp"
#include <iostream>

using namespace anvil;

GL::FrameBuffer::FrameBuffer()
{

}

GL::FrameBuffer::FrameBuffer(glm::vec2 size) : m_size(size)
{
	glGenFramebuffers(1, &m_handle);
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	//attach color texture
	glGenTextures(1, &m_texture_handle);
	glBindTexture(GL_TEXTURE_2D, m_texture_handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture_handle, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//needed for depth testing otherwise glEnable(GL_DEPTH_TEST) has no effekt
	glGenRenderbuffers(1, &m_render_handle);
	glBindRenderbuffer(GL_RENDERBUFFER, m_render_handle);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_render_handle);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw AnvilException("Failed to create FrameBuffer!", __FILE__, __LINE__);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GL::FrameBuffer::~FrameBuffer()
{
	if (m_handle)
	{
		glDeleteFramebuffers(1, &m_handle);
		m_handle = 0;
	}
	if (m_texture_handle)
	{
		glDeleteTextures(1, &m_texture_handle);
		m_texture_handle = 0;
	}
	if (m_render_handle)
	{
		glDeleteRenderbuffers(1, &m_render_handle);
		m_render_handle = 0;
	}
}

void GL::FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	glViewport(0, 0, m_size.x, m_size.y);
}

void GL::FrameBuffer::BindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_handle);
}

void GL::FrameBuffer::Resize(glm::vec2 size)
{
	m_size = size;
	//glBindTexture(GL_TEXTURE_2D, m_texture_handle);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_texture_handle, 0);
}