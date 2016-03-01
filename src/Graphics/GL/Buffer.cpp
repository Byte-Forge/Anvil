/*
************************************
* Copyright (C) 2016 ByteForge
* Buffer.cpp
************************************
*/

#include "Buffer.hpp"
#include "flextGL.h"

using namespace anvil;

GL::Buffer::Buffer(BufferType type) : m_type(type) , m_handle(0)
{
	glGenBuffers(1, &m_handle);
}

GL::Buffer::~Buffer()
{
	if (m_handle)
	{
		glDeleteBuffers(1, &m_handle);
		m_handle = 0;
	}	
}

void GL::Buffer::Bind()
{
	glBindBuffer(m_type, m_handle);
}

void GL::Buffer::Update(size_t bufferSize, const void* data, DrawType draw)
{
	glBufferData(m_type, bufferSize, data, draw);
}