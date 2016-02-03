//
// Created by stephan on 12.11.15.
//
#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>

namespace hpse
{
    class Audio
    {
    public:
        Audio();
        ~Audio();
    private:
        void EnumerateDevices(const ALCchar *devices);
    private:
        ALCdevice* m_device;
        ALCcontext* m_context;
		std::vector<std::string> m_deviceList;
    };
}



