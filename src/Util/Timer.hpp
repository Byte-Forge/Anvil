/*
************************************
* Copyright (C) 2016 ByteForge
* Timer.hpp
************************************
*/

#pragma once
#include <chrono>

namespace anvil
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