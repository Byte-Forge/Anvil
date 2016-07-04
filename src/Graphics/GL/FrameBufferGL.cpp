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
	glGenTextures(1, &m_color_tex);
	glBindTexture(GL_TEXTURE_2D, m_color_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_tex, 0);

	//attach depth texture
	glGenTextures(1, &m_depth_tex);
	glBindTexture(GL_TEXTURE_2D, m_depth_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_size.x, m_size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_tex, 0);

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
	if (m_color_tex)
	{
		glDeleteTextures(1, &m_color_tex);
		m_color_tex = 0;
	}
	if (m_depth_tex)
	{
		glDeleteTextures(1, &m_depth_tex);
		m_depth_tex = 0;
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
	glBindTexture(GL_TEXTURE_2D, m_color_tex);
}

void GL::FrameBuffer::BindDepthTexture()
{
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, m_depth_tex);
}