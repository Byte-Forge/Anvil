/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.cpp
************************************
*/

#include "Sound.hpp"
#include "../Exception.hpp"
using namespace anvil;

Sound::Sound(std::shared_ptr<SoundBuffer> buffer) : m_source(0)
{
    alGenSources(1,&m_source);
	ALuint bid = buffer->GetBufferId();
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
	alSourcei(m_source, AL_BUFFER, bid);
	error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
}

void Sound::Play()
{
	alSourcePlay(m_source);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
}

Sound::~Sound()
{
    if(m_source)
        alDeleteSources(1,&m_source);
}