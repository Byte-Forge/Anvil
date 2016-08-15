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
#include "Util/FileWatcher.hpp"
#include "WorldBuilder.hpp"

struct GLFWwindow;

namespace anvil
{
	class ResourceHandler;
	class Camera;
	class GUI;
	class Input;
	class Script;
	class Audio;
	class Frustum;
	class Graphics;
	class Map;

	enum Mode
	{
		MENU_MODE,
		WORLDBUILDER_MODE,
		GAME_MODE
	};

	/**
	* @class	Core
	*
	* @brief	The core of the engine
	*/
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

		/**
		* @fn	void Core::Quit();
		*
		* @brief	Quits the engine
		*/
		void Quit();

		void StartWorldBuilder();

		inline Util::Timer& GetTimer() { return m_timer; }
		inline Util::FPS& GetFPS() { return m_fps; }
		inline std::unique_ptr<GUI>& GetGUI() { return m_gui; }
		inline std::unique_ptr<Script>& GetScript() { return m_script; }
		inline std::unique_ptr<Graphics>& GetGraphics() { return m_graphics; }
		inline std::unique_ptr<ResourceHandler>& GetResources() { return m_resources; }
		inline std::shared_ptr<Camera>& GetCamera() { return m_camera; } 
		inline void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }
		inline std::unique_ptr<Input>& GetInput() { return m_input; }
		inline std::shared_ptr<Map>& GetMap() { return m_map; }
		inline void SetMap(std::shared_ptr<Map>& map) { m_map = map; }
		inline glm::vec2 GetResolution() { return m_resolution; }
		inline glm::vec2 GetFrameBufferScale() { return m_frameBufferScale; }
		inline void SetResolution(glm::vec2 res) { m_resolution = res; }
		inline GLFWwindow* GetWindow() { return m_window; }
		inline std::unique_ptr<WorldBuilder>& GetWorldBuilder() { return m_worldBuilder; }

		inline Mode GetMode() { return m_mode; }
		inline void SetMode(Mode mode) { m_mode = mode; }

		static inline Core* GetCore() { return m_instance; }

	private:
		static Core* m_instance;
		Mode m_mode;

		GLFWwindow* m_window;
		std::unique_ptr<ResourceHandler> m_resources;
		std::unique_ptr<Graphics> m_graphics;
		std::unique_ptr<GUI> m_gui;
		std::unique_ptr<Script> m_script;
		std::unique_ptr<Audio> m_audio;
		std::shared_ptr<Camera> m_camera;
		std::unique_ptr<Frustum> m_frustum;
		std::unique_ptr<Input> m_input;
		std::unique_ptr<WorldBuilder> m_worldBuilder;
		std::shared_ptr<Map> m_map;
		Util::Timer m_timer;
		Util::FPS m_fps;
		glm::vec2 m_resolution;
		glm::vec2 m_frameBufferScale;	//used for retina displays etc.

	private:
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void UnicodeCallback(GLFWwindow* window, unsigned int unicode);
		static void MouseCallback(GLFWwindow* window, int key, int action, int mods);
		static void MousePosCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double x, double y);
		static void ErrorCallback(int error, const char* description);
		static void ResizeCallback(GLFWwindow* window, int width, int height);
	};
}