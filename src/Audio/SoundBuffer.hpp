/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.hpp
************************************
*/

#pragma once
#if __APPLE__
#include <OpenAL/al.h>
#else
#include <AL/al.h>
#endif

#include "../Core/IResource.hpp"

namespace anvil
{
    class SoundBuffer : public IResource
    {
    public:
        SoundBuffer();
        ~SoundBuffer();
    private:
        ALuint m_buffer;
    };
}


