//
// Created by stephan on 17.11.15.
//

#include "Sound.hpp"
using namespace hpse;

Sound::Sound() : m_source(0)
{
    alGenSources(1,&m_source);
}

Sound::~Sound()
{
    if(m_source)
        alDeleteSources(1,&m_source);
}