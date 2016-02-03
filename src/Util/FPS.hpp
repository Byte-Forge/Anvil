#pragma once
#include <chrono>
#include <deque>

namespace hpse
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