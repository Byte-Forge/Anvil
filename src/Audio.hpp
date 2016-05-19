/*
************************************
* Copyright (C) 2016 ByteForge
* Audio.hpp
************************************
*/

#pragma once
#if __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include <vector>
#include <string>


namespace anvil
{
    /**
     * @class	Audio
     *
     * @brief	Manages audio devices and handles playback of sound files (.wav and .opus)
     */
    class Audio
    {
    public:

        /**
         * @fn	Audio::Audio();
         *
         * @brief	Default constructor.
         */
        Audio();

        /**
         * @fn	Audio::~Audio();
         *
         * @brief	Destructor.
         */
        ~Audio();

		/**
		* @fn	void Audio::PlaySound(const std::string& name);
		*
		* @brief	Plays a sound specified by name
		*
		* @param	name	The name of the sound that should be played
		*/
		void PlaySound(const std::string& name);

		/**
		* @fn	void Audio::PlayMusic(const std::string& name);
		*
		* @brief	Plays a music file specified by name
		*
		* @param	name	The name of the music file that should be played
		*/
		void PlayMusic(const std::string& name);

    private:
        ALCdevice* m_device;
        ALCcontext* m_context;
		std::vector<std::string> m_deviceList;

	private:

		void EnumerateDevices(const ALCchar *devices);
    };
}



