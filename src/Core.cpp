/*
************************************
* Copyright (C) 2016 ByteForge
* Core.cpp
************************************
*/

#include "Core.hpp" 
#include "Math/Collision.hpp"
#include "Util/FPS.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace anvil;

Core* Core::m_instance = nullptr;


void Core::ErrorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

void Core::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	auto& gui = Core::GetCore()->GetGUI();
	if (action == GLFW_PRESS)
		gui->KeyDown(key,mods);
	else if (action == GLFW_RELEASE)
		gui->KeyReleased(key, mods);
}

Core::Core()
{
	m_instance = this;
	
	if (!glfwInit())
		throw AnvilException("Failed to initialize glfw!", __FILE__, __LINE__);

	glfwSetErrorCallback(ErrorCallback);

	#ifdef ANVIL_USE_VULKAN
	if (glfwVulkanSupported())
	{
		std::cout << "Vulkan Driver available!" << std::endl;
	}
	#endif
	m_window = glfwCreateWindow(800, 600, "anvil engine", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSwapInterval(0);
	m_resources = std::make_unique<ResourceHandler>();
	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>();
	m_script = std::make_unique<Script>();
	m_gui = std::make_unique<GUI>(m_window);
	m_camera = std::make_unique<Camera>();

	m_script->LoadFile("start.lua");

	m_map = std::make_unique<Map>();
}

Core::~Core()
{
	glfwTerminate();
}

void Core::Run()
{
	//mouse variables
	int x_old = 0; 
	int y_old = 0; 
	int delta_x = 0;
	int delta_y = 0;
	int delta_wheel = 0;

	while (!glfwWindowShouldClose(m_window))
	{
		m_timer.Update();
		m_fps.Update();
		m_graphics->Clear();
		m_gui->Update();
		m_script->Update();
		m_camera->Update();
		
		m_graphics->Render();
		m_gui->Render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}