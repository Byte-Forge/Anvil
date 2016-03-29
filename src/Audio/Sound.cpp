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
	alSourcef(m_source, AL_PITCH, 1);
	// check for errors
	alSourcef(m_source, AL_GAIN, 1);
	// check for errors
	alSource3f(m_source, AL_POSITION, 0, 0, 0);
	// check for errors
	alSource3f(m_source, AL_VELOCITY, 0, 0, 0);
	// check for errors
	alSourcei(m_source, AL_LOOPING, AL_FALSE);
}

void Sound::Play()
{
	alSourcef(m_source, AL_GAIN, 255.0f);
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