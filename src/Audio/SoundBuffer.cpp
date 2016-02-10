/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.cpp
************************************
*/

#include "SoundBuffer.hpp"
#include <AL/alc.h>

using namespace anvil;

SoundBuffer::SoundBuffer() : m_buffer(0)
{
    alGenBuffers(1,&m_buffer);
}

SoundBuffer::~SoundBuffer()
{
    if(m_buffer)
        alDeleteBuffers(1,&m_buffer);
}