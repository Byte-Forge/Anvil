/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.hpp
************************************
*/

#pragma once
#if __APPLE__
#include <OpenAL/al.h>
#else
#include <AL/al.h>
#endif

#include "../Core/IResource.hpp"

namespace anvil
{
    /**
     * @class	SoundBuffer
     *
     * @brief	Buffer for sound.
     */
    class SoundBuffer : public IResource
    {
    public:

        /**
         * @fn	SoundBuffer::SoundBuffer();
         *
         * @brief	Default constructor.
         */
        SoundBuffer();

        /**
         * @fn	SoundBuffer::~SoundBuffer();
         *
         * @brief	Destructor.
         */
        ~SoundBuffer();

		/**
		 * @fn	bool SoundBuffer::Load(const std::string& path);
		 *
		 * @brief	Loads the given .wav file and stores it in this SoundBufffer.
		 *
		 * @param	path	The path of a .wav file to load.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool Load(const std::string& path);

		inline ALuint GetBufferId() { return m_buffer; }


		double GetDuration();
    private:
        ALuint m_buffer;
		ALsizei m_size;
		ALsizei m_frequency;
		ALenum m_format;
		double m_length;
    };
}


