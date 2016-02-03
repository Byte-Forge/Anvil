#pragma once
#include <chrono>

namespace hpse
{
	namespace Util
	{
		class Timer
		{
		public:
			Timer();
			void Update();
			//get elapsed time in Microseconds
			inline long int GetElapsedTime()
			{
				return m_elapsed;
			}
		private:
			std::chrono::high_resolution_clock::time_point m_last;
			long int m_elapsed;
		};
	}
}