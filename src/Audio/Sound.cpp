/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.cpp
************************************
*/

#include "Sound.hpp"
#include "../Exception.hpp"
using namespace anvil;

const std::string alErrorString(int err)
{
	switch (err)
	{
	case AL_NO_ERROR:
		return "AL_NO_ERROR";
	case AL_INVALID_NAME:
		return "AL_INVALID_NAME";
	case AL_INVALID_ENUM:
		return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE:
		return "AL_INVALID_VALUE";
	case AL_INVALID_OPERATION:
		return "AL_INVALID_OPERATION";
	case AL_OUT_OF_MEMORY:
		return "AL_OUT_OF_MEMORY";
	default:
		return "";
	}
}


Sound::Sound(std::shared_ptr<SoundBuffer> buffer) : m_source(0)
{
    alGenSources(1,&m_source);
	ALuint bid = buffer->GetBufferId();
	ALenum error = alGetError();
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
	alSourcei(m_source, AL_BUFFER, bid);

	error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
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