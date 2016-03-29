/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.hpp
************************************
*/

#pragma once
#if __APPLE__
#include <OpenAL/al.h>
#else
#include <AL/al.h>
#endif
#include "SoundBuffer.hpp"

namespace anvil
{
    /**
     * @class	Sound
     *
     * @brief	A sound.
     */
    class Sound
    {
    public:

        /**
         * @fn	Sound::Sound(SoundBuffer buffer);
         *
         * @brief	Default constructor.
         *
         * @param	buffer	The soundbuffer that should be played.
         */
        Sound(SoundBuffer buffer);

        /**
         * @fn	Sound::~Sound();
         *
         * @brief	Destructor.
         */
        ~Sound();

    private:
        ALuint  m_source;
    };
}


