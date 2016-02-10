/*
************************************
* Copyright (C) 2016 ByteForge
* Sound.cpp
************************************
*/

#include "Sound.hpp"
using namespace anvil;

Sound::Sound() : m_source(0)
{
    alGenSources(1,&m_source);
}

Sound::~Sound()
{
    if(m_source)
        alDeleteSources(1,&m_source);
}