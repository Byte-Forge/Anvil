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
		~Input();

		/**
		 * @fn	void Input::SetKeyState(int key, int action);
		 *
		 * @brief	Sets key state.

		 * @param	key   	The key.
		 * @param	action	The action.
		 */
		void SetKeyState(int key, int action);

		/**
		 * @fn	void Input::SetMouseState(int key, int action, int mods);
		 *
		 * @brief	Sets mouse key states.
		 *
		 * @param	key   	The key.
		 * @param	action	The action.
		 * @param	mods  	The mods.
		 */
		void SetMouseState(int key, int action, int mods);

		/**
		 * @fn	void Input::SetMousePosition(int x, int y);
		 *
		 * @brief	Sets mouse position.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		void SetMousePosition(int x, int y);

		/**
		 * @fn	void Input::SetMouseWheelDelta(double x, double y);
		 *
		 * @brief	Sets mouse wheel delta (how much it moved x and y direction).
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		void SetMouseWheelDelta(double x, double y);

		/**
		 * @fn	void Input::Update(const std::unique_ptr<Camera>& cam, const std::shared_ptr<IRenderer>& renderer);
		 *
		 * @brief	Processes actions dependand on the current user input;
		 *
		 * @param	cam			The camera.
		 * @param	renderer	The renderer.
		 */
		void Update(const std::unique_ptr<Camera>& cam, const std::shared_ptr<IRenderer>& renderer);

	private:

		/**
		 * @fn	int Input::TranslateState(int action);
		 *
		 * @brief	Translate key states from glfw to our custom states.
		 *
		 * @param	action	The action.
		 *
		 * @return	The translated state.
		 */
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