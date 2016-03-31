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

		void PlaySound(const std::string& name);
		void PlayMusic(const std::string& name);
    private:

        /**
         * @fn	void Audio::EnumerateDevices(const ALCchar *devices);
         *
         * @brief	Enumerate all available audio devices and print them to stdout. Only works when this extension is supported
         *
         * @param	devices		Pointer to the beginning of the device array
         */
        void EnumerateDevices(const ALCchar *devices);
    private:
        ALCdevice* m_device;
        ALCcontext* m_context;
		std::vector<std::string> m_deviceList;
    };
}



