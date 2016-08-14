/*
************************************
* Copyright (C) 2016 ByteForge
* GUI.hpp
************************************
*/

#pragma once
#include <memory>
#include <string>
#include <chrono>
#include <functional>
#include <map>
#include <spark/spark.hpp>


struct GLFWwindow;
namespace spark
{
	class Core;
	class View;
}


namespace anvil
{
	/**
	 * @class	GUI
	 *
	 * @brief	A graphical user interface.
	 */
	class GUI
	{
	public:

		/**
		 * @fn	GUI::GUI(GLFWwindow* window);
		 *
		 * @brief	Constructor.
		 *
		 * @param [in,out]	window	If non-null, the window.
		 */
		GUI(GLFWwindow* window);

		~GUI();

		/**
		 * @fn	void GUI::Update();
		 *
		 * @brief	Updates this object.
		 */
		void Update();

		/**
		 * @fn	void GUI::Render();
		 *
		 * @brief	Renders this object.
		 */
		void Render();

		/**
		 * @fn	void GUI::LoadFile(const std::string& file);
		 *
		 * @brief	Loads a file.
		 *
		 * @param	file	The file.
		 */
		void LoadFile(const std::string& file);

		/**
		 * @fn	void GUI::Resize(int width, int height);
		 *
		 * @brief	Resizes.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		void Resize(int width, int height);

		/**
		 * @fn	void GUI::MouseMove(int x, int y);
		 *
		 * @brief	Mouse move.
		 *
		 * @param	x   	The x coordinate.
		 * @param	y   	The y coordinate.
		 */
		void MouseMove(int x, int y);

		/**
		 * @fn	void GUI::SetMouseState(int key, int action, int mods);
		 *
		 * @brief	Mouse state.
		 *
		 * @param	key 	The key.
		 * @param	action	The action.
		 * @param	mods	The mods.
		 */
		void SetMouseState(int key, int action, int mods);

		void SetKeyState(int key, int action, int mods);

		void RestoreJustPressed() { m_view->RestoreJustPressed(); }

	private:
		std::string m_gui_file = "ui/ui.xml";
		bool m_tracked;

		int m_mouseX, m_mouseY;
		int m_frameTick;
		GLFWwindow* m_window;
		double m_accumulatedTime;
		double m_updateInterval;
		static const int UPDATES_PER_SECOND;
		std::shared_ptr<spark::Core> m_core;
		std::shared_ptr<spark::View> m_view;
	};
}