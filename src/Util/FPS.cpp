#include "FPS.hpp"
#include <numeric>
using namespace hpse;

std::chrono::high_resolution_clock::time_point FPS::m_start = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point FPS::m_end = std::chrono::high_resolution_clock::now();
double FPS::m_fps = 0;
double FPS::m_averageFps = 0;
std::deque<double> FPS::m_fps_list;

double FPS::GetFPS()
{
	return m_averageFps;
}

void FPS::Update()
{
	if (m_fps_list.size() > 100)
	{
		m_fps_list.pop_back();
	}
	m_end = std::chrono::high_resolution_clock::now();
	long int frametime_us = (std::chrono::duration_cast<std::chrono::microseconds>(m_end - m_start).count());
	long double frametime_s = frametime_us / 1000000.0f;
	m_fps = 1.f / frametime_s;
	m_fps_list.push_front(m_fps);
	m_start = m_end;
	m_averageFps = std::accumulate(m_fps_list.begin(), m_fps_list.end(), 0) / m_fps_list.size();
}
