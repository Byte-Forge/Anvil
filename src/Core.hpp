/*
************************************
* Copyright (C) 2016 ByteForge
* Core.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Util/Timer.hpp"
#include "Util/FPS.hpp"

struct GLFWwindow;

namespace anvil
{
	class ResourceHandler;
	class Map;
	class Camera;
	class GUI;
	class Input;
	class Script;
	class Graphics;
	class Audio;
	class Frustum;

	class Core
	{
	public: 

		/**
		 * @fn	Core::Core();
		 *
		 * @brief	Initialize all subsystems of the engine
		 */
		Core();

		/**
		 * @fn	Core::~Core();
		 *
		 * @brief	Delete all subsystems
		 */
		~Core();

		/**
		 * @fn	void Core::Run();
		 *
		 * @brief	Runs the engine
		 */
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

		inline std::unique_ptr<Input>& GetInput()
		{
			return m_input;
		}

		inline glm::vec2 GetResolution()
		{
			
			return m_resolution;
		}

		inline GLFWwindow* GetWindow()
		{
			return m_window;
		}

		void Quit();

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
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, int key, int action, int mods);
		static void MousePosCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double x, double y);
		static void ErrorCallback(int error, const char* description);
		static void ResizeCallback(GLFWwindow* window, int width, int height);
	private:
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
		std::unique_ptr<Input> m_input;
		Util::Timer m_timer;
		Util::FPS m_fps;
		glm::vec2 m_resolution;
	};
}