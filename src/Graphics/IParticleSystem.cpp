/*
************************************
* Copyright (C) 2016 ByteForge
* IParticleSystem.cpp
************************************
*/
#include "IParticleSystem.hpp"
#include "../Core.hpp"
using namespace anvil;

IParticleSystem::IParticleSystem() : m_spawnInterval(0),m_spawnRate(0),m_lifetime(0),
									m_spawnTime(0), m_currentTime(0)
{
	//register to rendermanger
}

void IParticleSystem::Start()
{
	m_currentTime = 0;
	m_spawnTime = 0;
	m_particles.clear();
}

void IParticleSystem::Update()
{
	long us = Core::GetCore()->GetTimer().GetElapsedTime();
	int ms = us / 1000;
}