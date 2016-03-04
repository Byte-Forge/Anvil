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
         * @fn	Sound::Sound();
         *
         * @brief	Default constructor.
         */
        Sound();

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


