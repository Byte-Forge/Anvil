/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.hpp
************************************
*/

#pragma once
#if __APPLE__
#include <OpenAL/alut.h>
#else
#include <AL/al.h>
#endif

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


