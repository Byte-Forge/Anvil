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
		//mouse variables
		int m_mouse_x = 0;
		int m_mouse_y = 0;
		int m_mouse_x_delta = 0;
		int m_mouse_y_delta = 0;
		double m_mouse_wheel_delta_x = 0;
		double m_mouse_wheel_delta_y = 0;

		std::map<int, int> m_keyInputs;
		std::map<int, int> m_mouseInputs;

	private:
		int TranslateState(int action);
	};
}