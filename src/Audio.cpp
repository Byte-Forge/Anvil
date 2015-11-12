//
// Created by stephan on 12.11.15.
//

#include "Audio.hpp"
#include <iostream>
#include <cstring>
using namespace hpse;

Audio::Audio() : m_device(nullptr), m_context(nullptr)
{
    m_device = alcOpenDevice(NULL);
    if(!m_device)
    {
        std::cout << "Failed to open audio device" << std::endl;
    }

    ALboolean enumeration;

    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
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

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0') {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}