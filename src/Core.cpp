/*
************************************
* Copyright (C) 2016 ByteForge
* Core.cpp
************************************
*/

#include "Core.hpp" 
#ifdef ANVIL_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include "Util/FPS.hpp"
#include "Exception.hpp"
#include "Core/Options.hpp"
#include <iostream>
#include "Graphics.hpp"
#include "Script.hpp"
#include "GUI.hpp"
#include "Audio.hpp"
#include "Types/Map.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/Frustum.hpp"
#include "Input.hpp"
#include "WorldBuilder.hpp"

using namespace anvil;

Core* Core::m_instance = nullptr;

void Core::ErrorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void Core::ResizeCallback(GLFWwindow *window, int width, int height)
{
	glm::vec2 scale = Core::GetCore()->GetFrameBufferScale();
	Core::GetCore()->GetGraphics()->Resize(width * scale.x, height * scale.y);
	Core::GetCore()->GetGUI()->Resize(width, height);
	Core::GetCore()->SetResolution(glm::vec2(width, height));
	if (Core::GetCore()->GetCamera() != nullptr)
	{
		Core::GetCore()->GetCamera()->SetRatio(width / height);
	}
}

void Core::MouseCallback(GLFWwindow* window, int key, int action, int mods)
{
	Core::GetCore()->GetInput()->SetMouseState(key, action, mods);
	Core::GetCore()->GetGUI()->SetMouseState(key, action, mods);
}

void Core::MousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Core::GetCore()->GetInput()->SetMousePosition(xpos, ypos);
	Core::GetCore()->GetGUI()->MouseMove(xpos,ypos);
}

void Core::ScrollCallback(GLFWwindow* window, double x, double y)
{
	Core::GetCore()->GetInput()->SetMouseWheelDelta(x, y);
}

void Core::Quit()
{
	glfwSetWindowShouldClose(m_window, true);
}

void Core::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	Core::GetCore()->GetInput()->SetKeyState(key, action);
	Core::GetCore()->GetGUI()->SetKeyState(key, action, mods);
}

Core::Core()
{
	m_instance = this;
	if (!Options::Load("options.json"))
		Options::Save("options.json");

	if (!glfwInit())
		throw AnvilException("Failed to initialize glfw!", __FILE__, __LINE__);

	glfwSetErrorCallback(ErrorCallback);
	Graphics::RenderBackend backend = Graphics::OpenGL;

	#ifdef ANVIL_USE_VULKAN
	if (glfwVulkanSupported())
	{
		std::cout << "Vulkan Driver available!" << std::endl;
		//backend = Graphics::Vulkan;
	}
	#endif
	 
	glfwWindowHint(GLFW_SAMPLES, 0); //set to 0 we do it ourselfes
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	m_window = glfwCreateWindow(Options::GetWidth(), Options::GetHeight(), "anvil engine", 
								Options::GetFullscreen() ? glfwGetPrimaryMonitor() : nullptr, nullptr);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	m_resolution.x = width;
	m_resolution.y = height;
	glfwGetFramebufferSize(m_window, &width, &height);
	m_frameBufferScale.x = width / m_resolution.x;
	m_frameBufferScale.y = height / m_resolution.y;

	glfwMakeContextCurrent(m_window);
	
	m_resources = std::make_unique<ResourceHandler>();
	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>(backend);
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_input = std::make_unique<Input>();
	m_script->LoadFile("start.lua");

	//m_audio->PlaySound("sound/test.wav");
	
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetWindowSizeCallback(m_window, ResizeCallback);
	glfwSetMouseButtonCallback(m_window, MouseCallback);
	glfwSetCursorPosCallback(m_window, MousePosCallback);
	glfwSetScrollCallback(m_window, ScrollCallback);
	glfwSwapInterval(0);

	m_mode = MENU_MODE;
	FileWatcher::Initialize();
	auto reload = [this](const fs::path &path) {
			std::cout << path << " needs recompile" << std::endl;
	};
	FileWatcher::AddPath("start.lua", reload);
}

Core::~Core()
{
	FileWatcher::Shutdown();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	glfwTerminate();	
}

void Core::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		m_gui->Update();
		m_script->Update();
		m_timer.Update();
		m_fps.Update();

		if (m_mode == WORLDBUILDER_MODE)
		{
			m_worldBuilder->Update();
		}
		
		if (m_mode == WORLDBUILDER_MODE || m_mode == GAME_MODE)
		{
			m_graphics->Clear();
			m_camera->Update();
			m_graphics->Render();
		}
	
		m_gui->Render();

		m_gui->RestoreJustPressed();
		m_input->RestoreJustPressed();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Core::StartWorldBuilder()
{
	m_graphics->GetRenderer()->Init();
	m_worldBuilder = std::make_unique<WorldBuilder>(); 
}