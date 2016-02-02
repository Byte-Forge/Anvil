#pragma once
#include <chrono>
#include <deque>

namespace hpse
{
	class FPS
	{
	public:
		static double GetFPS();
		static void Update();

	private:
		static std::chrono::high_resolution_clock::time_point m_start;
		static std::chrono::high_resolution_clock::time_point m_end;
		static double m_fps;
		static double m_averageFps;
		static std::deque<double> m_fps_list;
	};
}