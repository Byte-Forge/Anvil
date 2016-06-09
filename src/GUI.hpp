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
		 * @fn	void GUI::MouseMove(int x, int y,int mods);
		 *
		 * @brief	Mouse move.
		 *
		 * @param	x   	The x coordinate.
		 * @param	y   	The y coordinate.
		 * @param	mods	The mods.
		 */
		void MouseMove(int x, int y,int mods);

		/**
		 * @fn	void GUI::MousePressed(int key, int mods);
		 *
		 * @brief	Mouse pressed.
		 *
		 * @param	key 	The key.
		 * @param	mods	The mods.
		 */
		void MousePressed(int key, int mods);

		/**
		 * @fn	void GUI::MouseReleased(int key, int mods);
		 *
		 * @brief	Mouse released.
		 *
		 * @param	key 	The key.
		 * @param	mods	The mods.
		 */
		void MouseReleased(int key, int mods);

		/**
		 * @fn	void GUI::KeyDown(int key, int mods);
		 *
		 * @brief	Key down.
		 *
		 * @param	key 	The key.
		 * @param	mods	The mods.
		 */
		void KeyDown(int key, int mods);

		/**
		 * @fn	void GUI::KeyReleased(int key, int mods);
		 *
		 * @brief	Key released.
		 *
		 * @param	key 	The key.
		 * @param	mods	The mods.
		 */
		void KeyReleased(int key, int mods);

	private:
		int m_mouseX, m_mouseY;
		int m_frameTick;
		GLFWwindow* m_window;
		double m_accumulatedTime;
		double m_updateInterval;
		static const int UPDATES_PER_SECOND;
		std::unique_ptr<spark::Core> m_core;
		std::shared_ptr<spark::View> m_view;

		std::shared_ptr<spark::ILabel> m_fps;
		std::shared_ptr<spark::ILabel> m_renderedTris;
	};
}