/*
************************************
* Copyright (C) 2016 ByteForge
* Audio.cpp
************************************
*/

#include "Audio.hpp"
#include "Core.hpp"
#include "Core/ResourceHandler.hpp"
#include <iostream>
#include <cstring>
#include "Exception.hpp"
using namespace anvil;

Audio::Audio() : m_device(nullptr), m_context(nullptr)
{
    m_device = alcOpenDevice(NULL);
    if(!m_device)
		throw AnvilException("Failed to open audio device", __FILE__, __LINE__);

    m_context = alcCreateContext(m_device, NULL);
    if(!alcMakeContextCurrent(m_context))
		throw AnvilException("Failed to create OpenAL context", __FILE__, __LINE__);
    
	ALCenum errorAlc = alcGetError(m_device);
	if (errorAlc != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);

	ALfloat listenerOri[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0, 0, 1.0f);
	// check for errors
	alListener3f(AL_VELOCITY, 0, 0, 0);
	// check for errors
	alListenerfv(AL_ORIENTATION, listenerOri);

	ALenum error = alGetError();
	if (error != AL_NO_ERROR)
		throw AnvilException("Error in OpenAL!", __FILE__, __LINE__);
}

Audio::~Audio()
{
    alcMakeContextCurrent(NULL);

    if(m_context)
        alcDestroyContext(m_context);

    if(m_device)
        alcCloseDevice(m_device);
}

void Audio::PlaySound(const std::string & name)
{
	auto buffer = Core::GetCore()->GetResources()->GetSound(name);
	auto  sound = std::make_shared<Sound>(buffer);
	sound->Play();
	m_sounds.push_back(sound);
}

void Audio::PlayMusic(const std::string & name)
{
}

void Audio::EnumerateDevices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    while (device && *device != '\0' && next && *next != '\0') 
	{
		m_deviceList.push_back(device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
}