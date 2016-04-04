/*
************************************
* Copyright (C) 2016 ByteForge
* FPS.cpp
************************************
*/

#include "FPS.hpp"
#include <numeric>
#include "../Core.hpp"

using namespace anvil;

double Util::FPS::GetFPS()
{
	return m_averageFps;
}

void Util::FPS::Update()
{
	if (m_fps_list.size() > 100)
	{
		m_fps_list.pop_back();
	}

	long int frametime_us = Core::GetCore()->GetCore()->GetTimer().GetElapsedTime();
	long double frametime_s = frametime_us / 1000000.0f;
	m_fps = 1.f / frametime_s;
	m_fps_list.push_front(m_fps);
	m_averageFps = std::accumulate(m_fps_list.begin(), m_fps_list.end(), 0) / m_fps_list.size();
}
