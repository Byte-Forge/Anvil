/*
************************************
* Copyright (C) 2016 ByteForge
* Audio.cpp
************************************
*/

#include "Audio.hpp"
#include <iostream>
#include <cstring>

using namespace anvil;

Audio::Audio() : m_device(nullptr), m_context(nullptr)
{
    m_device = alcOpenDevice(NULL);
    if(!m_device)
    {
        std::cout << "Failed to open audio device" << std::endl;
    }

    ALboolean enumeration;

    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_TRUE)
    {
        EnumerateDevices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    }
    else
    {
        std::cout << "Can not enumerate audio devices" << std::endl;
    }

    m_context = alcCreateContext(m_device,NULL);
    if(!alcMakeContextCurrent(m_context))
    {
        std::cout << "Failed to create OpenAL context" << std::endl;
    }
}

Audio::~Audio()
{
    alcMakeContextCurrent(NULL);

    if(m_context)
        alcDestroyContext(m_context);

    if(m_device)
        alcCloseDevice(m_device);
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