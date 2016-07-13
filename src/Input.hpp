/*
************************************
* Copyright (C) 2016 ByteForge
* Input.hpp
************************************
*/
#pragma once
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#define JUST_RELEASED -1
#define RELEASED 0
#define PRESSED 1

namespace anvil
{
	/**
	 * @class	Input
	 *
	 * @brief	Handles the input from the user.
	 */
	class Input
	{
	public:

		/**
		 * @fn	Input::Input();
		 *
		 * @brief	Default constructor.
		 */
		Input();

		/**
		* @fn	Input::~Input();
		*
		* @brief	Default destructor.
		*/
		~Input();

		/**
		 * @fn	void Input::SetKeyState(const int key, int action);
		 *
		 * @brief	Sets key state.
		 *
		 * @param	key   	The key.
		 * @param	action	The action.
		 */
		void SetKeyState(const int key, int action);

		/**
		 * @fn	void Input::SetMouseState(const int key, int action, const int mods);
		 *
		 * @brief	Sets mouse key states.
		 *
		 * @param	key   	The key.
		 * @param	action	The action.
		 * @param	mods  	The mods.
		 */
		void SetMouseState(const int key, int action, const int mods);

		/**
		 * @fn	void Input::SetMousePosition(const int x, const int y);
		 *
		 * @brief	Sets mouse position.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		void SetMousePosition(const int x, const int y);

		/**
		 * @fn	void Input::SetMouseWheelDelta(const double x, const double y);
		 *
		 * @brief	Sets mouse wheel delta (how much it moved x and y direction).
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		void SetMouseWheelDelta(const double x, const double y);

		inline int MouseButtonPressed(int button) { if (m_mouseInputs[button] == PRESSED) { return 1; } return 0; }
		inline int MouseButtonReleased(int button) { if (m_mouseInputs[button] == RELEASED) { return 1; } return 0; }
		inline int MouseButtonJustReleased(int button) { if (m_mouseInputs[button] == JUST_RELEASED) { m_mouseInputs[button] = RELEASED; return 1; } return 0; }
		inline glm::vec2 GetMousePosition() { return glm::vec2(m_mouse_x, m_mouse_y); }
		inline glm::vec2 GetMouseDelta() { glm::vec2 out = glm::vec2(m_mouse_x_delta, m_mouse_y_delta); m_mouse_x_delta = 0; m_mouse_y_delta = 0; return out; }
		inline double GetMouseWheelDeltaY() { double out = m_mouse_wheel_delta_y; m_mouse_wheel_delta_y = 0.0; return out; }

		inline int KeyPressed(int key) { if (m_keyInputs[key] == PRESSED) { return 1; } return 0; }
		inline int KeyReleased(int key) { if (m_keyInputs[key] == RELEASED) { return 1; } return 0; }
		inline int KeyJustReleased(int key) { if (m_keyInputs[key] == JUST_RELEASED) { m_keyInputs[key] = RELEASED; return 1; } return 0; }

	private:
		int TranslateState(int action);

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
	};
}