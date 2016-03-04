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

    private:
        ALuint m_buffer;
    };
}


