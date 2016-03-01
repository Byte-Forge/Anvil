/*
************************************
* Copyright (C) 2016 ByteForge
* Input.hpp
************************************
*/
#pragma once
#include <map>
#include <memory>
#include "Graphics/Camera.hpp"
#include "Graphics/IRenderer.hpp"

namespace anvil
{
	class Input
	{
	public:
		Input();
		~Input();

		void SetKeyState(int key, int action);
		void SetMouseState(int key, int x, int y);
		void SetMousePosition(int x, int y);
		void SetMouseWheelDelta(double x, double y);
		void Update(const std::unique_ptr<Camera>& cam, const std::shared_ptr<IRenderer>& renderer);

	private:
		//mouse variables
		int m_mouse_x = 0;
		int m_mouse_y = 0;
		int m_mouse_x_delta = 0;
		int m_mouse_y_delta = 0;
		double m_mouse_wheel_delta_x = 0;
		double m_mouse_wheel_delta_y = 0;

		std::map<int, int> m_keyInputs;
		std::map<int, int> m_mouseInputs;

		int TranslateState(int action);
	};
}