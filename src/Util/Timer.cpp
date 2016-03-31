/*
************************************
* Copyright (C) 2016 ByteForge
* Timer.cpp
************************************
*/

#include "Timer.hpp"
#include <iostream>

using namespace anvil;

Util::Timer::Timer() : m_elapsed(1)
{
	m_last = std::chrono::high_resolution_clock::now();
}

void Util::Timer::Update()
{
	auto current = std::chrono::high_resolution_clock::now();
	m_elapsed = (std::chrono::duration_cast<std::chrono::microseconds>(current - m_last).count());
	m_last = current;
}
