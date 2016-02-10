/*
************************************
* Copyright (C) 2016 ByteForge
* Audio.hpp
************************************
*/

#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>

namespace anvil
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



