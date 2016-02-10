/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.hpp
************************************
*/

#pragma once
#include <AL/al.h>

namespace anvil
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


