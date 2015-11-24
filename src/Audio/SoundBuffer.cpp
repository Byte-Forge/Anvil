//
// Created by stephan on 24.11.15.
//

#include "SoundBuffer.hpp"
#include <AL/alc.h>
using namespace hpse;

SoundBuffer::SoundBuffer() : m_buffer(0)
{
    alGenBuffers(1,&m_buffer);
}

SoundBuffer::~SoundBuffer()
{
    if(m_buffer)
        alDeleteBuffers(1,&m_buffer);
}