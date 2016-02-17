/*
************************************
* Copyright (C) 2016 ByteForge
* Core.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Graphics.hpp"
#include "Script.hpp"
#include "GUI.hpp"
#include "Audio.hpp"
#include "Types/Map.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Frustum.hpp"
#include "Util/Timer.hpp"
#include "Util/FPS.hpp"

namespace anvil
{
	class Core
	{
	public: 
		Core();
		~Core();

		void Run();

		inline std::unique_ptr<GUI>& GetGUI()
		{
			return m_gui;
		}

		inline std::unique_ptr<Script>& GetScript()
		{
			return m_script;
		}

		inline std::unique_ptr<Graphics>& GetGraphics()
		{
			return m_graphics;
		}

		inline std::unique_ptr<ResourceHandler>& GetResources()
		{
			return m_resources;
		}

		inline std::unique_ptr<Map>& GetMap()
		{
			return m_map;
		}

		inline std::unique_ptr<Camera>& GetCamera()
		{
			return m_camera;
		} 

		inline glm::vec2 GetResolution()
		{
			glm::vec2 res;
			int width, height;
			glfwGetWindowSize(m_window, &width, &height);
			res.x = width;
			res.y = height;
			return res;
		}

		inline GLFWwindow* GetWindow()
		{
			return m_window;
		}

		inline void Quit()
		{
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}

		static inline Core* GetCore()
		{
			return m_instance;
		}

		Util::Timer& GetTimer()
		{
			return m_timer;
		}

		Util::FPS& GetFPS()
		{
			return m_fps;
		}

	private:
		enum KEYSTATE 
		{
			JUST_RELEASED = -1,
			NOT_PRESSED = 0,
			PRESSED = 1,
		};

		static Core* m_instance;

		GLFWwindow* m_window;
		std::unique_ptr<ResourceHandler> m_resources;
		std::unique_ptr<Graphics> m_graphics;
		std::unique_ptr<GUI> m_gui;
		std::unique_ptr<Script> m_script;
		std::unique_ptr<Audio> m_audio;
		std::unique_ptr<Map> m_map;
		std::unique_ptr<Camera> m_camera;
		std::unique_ptr<Frustum> m_frustum;
		Util::Timer m_timer;
		Util::FPS m_fps;
		std::map<int, int> m_keyInputs; 
		std::map<int, int> m_mouseInputs; 
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void ErrorCallback(int error, const char* description);
	};
}