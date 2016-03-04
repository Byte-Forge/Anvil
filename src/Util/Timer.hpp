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
		/**
		 * @class	Timer
		 *
		 * @brief	A timer.
		 */
		class Timer
		{
		public:

			/**
			 * @fn	Timer::Timer();
			 *
			 * @brief	Default constructor.
			 */
			Timer();

			/**
			 * @fn	void Timer::Update();
			 *
			 * @brief	Updates this object.
			 */
			void Update();

			inline long int GetElapsedTime() { return m_elapsed; }

		private:
			std::chrono::high_resolution_clock::time_point m_last;
			long int m_elapsed;
		};
	}
}