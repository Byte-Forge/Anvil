/*
************************************
* Copyright (C) 2016 ByteForge
* GUI.hpp
************************************
*/

#pragma once
#include <memory>
#include <string>
#include <Rocket/Core.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "./GUI/SystemInterface.hpp"
#include "./GUI/ScriptInterface.hpp"

namespace anvil
{

	class GUI
	{
	public:
		GUI(GLFWwindow* window);
		~GUI();

		void Update();
		void Render();
		void LoadURL(const std::string& url);
		void LoadFile(const std::string& file);
		void Resize(int width, int height);

		//Events
		void MouseMove(int x, int y,int mods);
		void MousePressed(int key, int mods);
		void MouseReleased(int key, int mods);
		void KeyDown(int key, int mods);
		void KeyReleased(int key, int mods);
	private:
		int m_mouseX, m_mouseY;
		int m_frameTick;
		SystemInterface m_system;
		ScriptInterface m_script;
		Rocket::Core::Context* m_context;
		GLFWwindow* m_window;
		double m_accumulatedTime;
		double m_updateInterval;
		static const int UPDATES_PER_SECOND;
	};
}