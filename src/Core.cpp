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

void Core::ResizeCallback(GLFWwindow * window, int width, int height)
{
	Core::GetCore()->GetGraphics()->Resize(width, height);
	Core::GetCore()->GetGUI()->Resize(width, height);
}

void Core::MouseCallback(GLFWwindow* window, int key, int x, int y)
{

}

void Core::ScrollCallback(GLFWwindow* window, double x, double y)
{
	Core::GetCore()->GetCamera()->Zoom(y);
}

void Core::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	const auto& cam = Core::GetCore()->GetCamera();
	const auto& renderer = Core::GetCore()->GetGraphics()->GetRenderer();

	switch (key)
	{
	case GLFW_KEY_W:
		cam->Move(Direction::FOREWARD);
		break;
	case GLFW_KEY_S:
		cam->Move(Direction::BACK);
		break;
	case GLFW_KEY_A:
		cam->Move(Direction::LEFT);
		break;
	case GLFW_KEY_D:
		cam->Move(Direction::RIGHT);
		break;
	case GLFW_KEY_Q:
		cam->Rotate(Direction::LEFT);
		break;
	case GLFW_KEY_E:
		cam->Rotate(Direction::RIGHT);
		break;
	case GLFW_KEY_F1:
		renderer->ToggleWireframeMode();
		break;
	case GLFW_KEY_F2:
		renderer->ToggleNormalsMode();
		break;
	}
	

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
	Graphics::RenderBackend backend = Graphics::OpenGL;

	#ifdef ANVIL_USE_VULKAN
	if (glfwVulkanSupported())
	{
		std::cout << "Vulkan Driver available!" << std::endl;
		//backend = Graphics::Vulkan;
	}
	#endif
	m_window = glfwCreateWindow(800, 600, "anvil engine", NULL, NULL);

	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	m_resolution.x = width;
	m_resolution.y = height;

	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, KeyCallback);
	glfwSetWindowSizeCallback(m_window,ResizeCallback);
	glfwSetMouseButtonCallback(m_window, MouseCallback);
	glfwSetScrollCallback(m_window, ScrollCallback);
	glfwSwapInterval(0);
	m_resources = std::make_unique<ResourceHandler>();
	m_audio = std::make_unique<Audio>();
	m_graphics = std::make_unique<Graphics>(backend);
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