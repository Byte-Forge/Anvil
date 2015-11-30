//
// Created by stephan on 17.11.15.
//

#pragma once
#include <AL/al.h>

namespace hpse
{
    class Sound
    {
    public:
        Sound();
        ~Sound();
    private:
        ALuint  m_source;
    };
}


