/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.hpp
************************************
*/

#pragma once
#include <AL/al.h>
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


