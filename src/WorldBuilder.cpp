/*
************************************
* Copyright (C) 2016 ByteForge
* WorldBuilder.cpp
************************************
*/

#include "WorldBuilder.hpp"
#include "Core.hpp"
#include "Graphics/Camera.hpp"
#include "Types/Map.hpp"
#include "Input.hpp"
#include "Objects/Entity.hpp"
#include <GLFW/glfw3.h>

using namespace anvil;

WorldBuilder::WorldBuilder()
{
	m_camera = std::make_shared<Camera>(glm::vec3(-30.0, 30.0, -30.0), glm::vec3(0.0, 0.0, 0.0));
	Core::GetCore()->SetCamera(m_camera);

	m_map = std::make_shared<Map>();
	Core::GetCore()->SetMap(m_map);
}

WorldBuilder::~WorldBuilder()
{

}

void WorldBuilder::Update()
{
	UpdateUserInput();
}

void WorldBuilder::UpdateUserInput()
{
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_W))
		m_camera->Move(Direction::FOREWARD);
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_S))
		m_camera->Move(Direction::BACK);
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_A))
		m_camera->Move(Direction::LEFT);
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_D))
		m_camera->Move(Direction::RIGHT);
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_Q))
		m_camera->Rotate(Direction::LEFT);
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_E))
		m_camera->Rotate(Direction::RIGHT);

	if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		glm::vec3 position;
		if (m_map->GetTerrain()->GetMousePositionInWorldSpace(Core::GetCore()->GetInput()->GetMousePosition(), position))
		{
		std::shared_ptr<Entity> e = Core::GetCore()->GetResources()->GetEntity("entities/units/isengard/urukhai_crossbow.json");
		e->AddInstance(position);
		m_map->GetTerrain()->SetHeight(position, 10.0f, 3);
		m_map->GetTerrain()->SetMaterial(position, 10.0f, 0);
		}
	}

	if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		m_camera->Move(Core::GetCore()->GetInput()->GetMouseDelta());
	}
	else if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_3))
		m_camera->Rotate(Core::GetCore()->GetInput()->GetMouseDelta().x);

	m_camera->Zoom(Core::GetCore()->GetInput()->GetMouseWheelDeltaY());
}