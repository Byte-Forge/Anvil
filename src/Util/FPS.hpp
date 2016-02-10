/*
************************************
* Copyright (C) 2016 ByteForge
* FPS.hpp
************************************
*/

#pragma once
#include <chrono>
#include <deque>

namespace anvil
{
	namespace Util
	{
		class FPS
		{
		public:
			double GetFPS();
			void Update();

		private:
			double m_fps;
			double m_averageFps;
			std::deque<double> m_fps_list;
		};
	}
}