/*
************************************
* Copyright (C) 2016 ByteForge
* Input.cpp
************************************
*/

#include "Input.hpp"
#include <iostream>

using namespace anvil;

Input::Input()
{

}

Input::~Input()
{

}

void Input::SetKeyState(const int key, int action)
{
	action = TranslateState(action);
	m_keyInputs[key] = action;
}

void Input::SetMouseState(const int key, int action, const int mods)
{
	action = TranslateState(action);
	m_mouseInputs[key] = action;
}

void Input::SetMousePosition(const int x, const int y)
{
	m_mouse_x_delta = x - m_mouse_x;
	m_mouse_y_delta = y - m_mouse_y;
	m_mouse_x = x;
	m_mouse_y = y;
}

void Input::SetMouseWheelDelta(const double x, const double y)
{
	m_mouse_wheel_delta_x = x;
	m_mouse_wheel_delta_y = y;
}

void Input::RestoreJustPressed()
{
	for (auto key : m_keyInputs)
	{
		if (key.second == JUST_RELEASED)
			key.second = RELEASED;
	}
	for (auto button : m_mouseInputs)
	{
		if (button.second == JUST_RELEASED)
			button.second = RELEASED;
	}
}