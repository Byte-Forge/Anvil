#include "Buffer.hpp"
#include "flextGL.h"

using namespace hpse;

GL::Buffer::Buffer(BufferType type)
{
	glGenBuffers(1, &m_handle);
	m_type = type;
}

GL::Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_handle);
	m_handle = 0;
}

void GL::Buffer::Bind()
{
	glBindBuffer(m_type, m_handle);
}

void GL::Buffer::Update(unsigned int bufferSize, const void* data, DrawType draw)
{
	glBufferData(m_type, bufferSize, data, draw);
}