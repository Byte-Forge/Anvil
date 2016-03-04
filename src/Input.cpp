/*
************************************
* Copyright (C) 2016 ByteForge
* Input.cpp
************************************
*/

#include "Input.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#define JUST_RELEASED -1
#define RELEASED 0
#define PRESSED 1

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

void Input::Update(const std::unique_ptr<Camera>& cam, const std::shared_ptr<IRenderer>& renderer)
{
	if (m_keyInputs[GLFW_KEY_W] == PRESSED)
		cam->Move(Direction::FOREWARD);
	if (m_keyInputs[GLFW_KEY_S] == PRESSED)
		cam->Move(Direction::BACK);
	if (m_keyInputs[GLFW_KEY_A] == PRESSED)
		cam->Move(Direction::LEFT);
	if (m_keyInputs[GLFW_KEY_D] == PRESSED)
		cam->Move(Direction::RIGHT);
	if (m_keyInputs[GLFW_KEY_Q] == PRESSED)
		cam->Rotate(Direction::LEFT);
	if (m_keyInputs[GLFW_KEY_E] == PRESSED)
		cam->Rotate(Direction::RIGHT);
	if (m_keyInputs[GLFW_KEY_F1] == JUST_RELEASED)
	{
		renderer->ToggleWireframeMode();
		m_keyInputs[GLFW_KEY_F1] = RELEASED;
	}
	if (m_keyInputs[GLFW_KEY_F2] == JUST_RELEASED)
	{
		renderer->ToggleNormalsMode();
		m_keyInputs[GLFW_KEY_F2] = RELEASED;
	}

	//if (m_mouseInputs[GLFW_MOUSE_BUTTON_1] == PRESSED)
	//	std::cout << "left" << std::endl;

	if (m_mouseInputs[GLFW_MOUSE_BUTTON_2] == PRESSED)
	{
		cam->Move(glm::vec3(m_mouse_x_delta, 0.0, m_mouse_y_delta));
	}
	else if (m_mouseInputs[GLFW_MOUSE_BUTTON_3] == PRESSED)
		cam->Rotate(m_mouse_x_delta);

	cam->Zoom(m_mouse_wheel_delta_y);

	m_mouse_wheel_delta_y = 0.0;
	m_mouse_x_delta = 0;
	m_mouse_y_delta = 0;
}

int Input::TranslateState(int action)
{
	//change the stupid key states of glfw to our custom states
	if (action > 0)
		action = PRESSED;
	else
		action = JUST_RELEASED;
	return action;
}