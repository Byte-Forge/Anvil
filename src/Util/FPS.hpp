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
		/**
		 * @class	FPS
		 *
		 * @brief	Is used to display the FPS in debug mode.
		 */
		class FPS
		{
		public:

			/**
			 * @fn	double FPS::GetFPS();
			 *
			 * @brief	Gets the FPS.
			 *
			 * @return	The current FPS.
			 */
			double GetFPS();

			/**
			 * @fn	void FPS::Update();
			 *
			 * @brief	Updates this object.
			 */
			void Update();

		private:
			double m_fps;
			double m_averageFps;
			std::deque<double> m_fps_list;
		};
	}
}