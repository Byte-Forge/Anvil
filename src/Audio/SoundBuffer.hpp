//
// Created by stephan on 24.11.15.
//

#pragma once
#include <AL/al.h>
#include "../Core/IResource.hpp"

namespace hpse
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


