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
#include <memory>

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
        Sound(std::shared_ptr<SoundBuffer> buffer);

        /**
         * @fn	Sound::~Sound();
         *
         * @brief	Destructor.
         */
        ~Sound();

		/**
		* @fn	void Sound::Play();
		*
		* @brief	plays this sound.
		*/
		void Play();

		bool IsPlaying();

		void SetLooping(bool loop);
    private:
        ALuint  m_source;
		bool	m_loop;
    };
}


