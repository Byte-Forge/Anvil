/*
************************************
* Copyright (C) 2016 ByteForge
* Core.cpp
************************************
*/

#include "Core.hpp" 
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

using namespace anvil;

Core* Core::m_instance = nullptr;

void Core::ErrorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void Core::ResizeCallback(GLFWwindow * window, int width, int height)
{
	Core::GetCore()->GetGraphics()->Resize(width, height);
	Core::GetCore()->GetGUI()->Resize(width, height);
}

void Core::MouseCallback(GLFWwindow* window, int key, int action, int mods)
{
	Core::GetCore()->GetInput()->SetMouseState(key, action, mods);
	auto& gui = Core::GetCore()->GetGUI();
	if(action==GLFW_PRESS)
		gui->MousePressed(key,mods);
	else if(action==GLFW_RELEASE)
		gui->MouseReleased(key,mods);
}

void Core::MousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Core::GetCore()->GetInput()->SetMousePosition(xpos, ypos);
	Core::GetCore()->GetGUI()->MouseMove(xpos,ypos,0);
}

void Core::ScrollCallback(GLFWwindow* window, double x, double y)
{
	Core::GetCore()->GetInput()->SetMouseWheelDelta(x, y);
}

void Core::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	Core::GetCore()->GetInput()->SetKeyState(key, action);
	
	auto& gui = Core::GetCore()->GetGUI();
	if (action == GLFW_PRESS)
		gui->KeyDown(key, mods);
	else if (action == GLFW_RELEASE)
		gui->KeyReleased(key, mods);
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
	 
	m_window = glfwCreateWindow(Options::GetWidth(), Options::GetHeight(), "anvil engine", 
								Options::GetFullscreen() ? glfwGetPrimaryMonitor() : nullptr ,nullptr);

	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	m_resolution.x = width;
	m_resolution.y = height;

	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetWindowSizeCallback(m_window,ResizeCallback);
	glfwSetMouseButtonCallback(m_window, MouseCallback);
	glfwSetCursorPosCallback(m_window, MousePosCallback);
	glfwSetScrollCallback(m_window, ScrollCallback);
	glfwSwapInterval(0);
	m_resources = std::make_unique<ResourceHandler>();
	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>(backend);
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_camera = std::make_unique<Camera>();
	m_input = std::make_unique<Input>();

	m_script->LoadFile("start.lua");

	m_map = std::make_unique<Map>();

	m_audio->PlaySound("roll_over_01.wav");
}

Core::~Core()
{
	glfwTerminate();
}

void Core::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		m_timer.Update();
		m_fps.Update();
		m_graphics->Clear();
		m_gui->Update();
		m_script->Update();
		m_camera->Update();
		m_input->Update(m_camera, m_graphics->GetRenderer());

		m_graphics->Render();
		m_gui->Render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}