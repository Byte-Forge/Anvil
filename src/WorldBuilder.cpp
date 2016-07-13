/*
************************************
* Copyright (C) 2016 ByteForge
* WorldBuilder.cpp
************************************
*/

#include "WorldBuilder.hpp"
#include "Core.hpp"
#include "Core/ResourceHandler.hpp"
#include "Graphics/Camera.hpp"
#include "Types/Map.hpp"
#include "Input.hpp"
#include "Objects/Entity.hpp"
#include "Objects/Instance.hpp"
#include <GLFW/glfw3.h>

using namespace anvil;

WorldBuilder::WorldBuilder()
{
	m_camera = std::make_shared<Camera>(glm::vec3(-30.0, 30.0, -30.0), glm::vec3(0.0, 0.0, 0.0));
	Core::GetCore()->SetCamera(m_camera);

	m_map = std::make_shared<Map>();
	Core::GetCore()->SetMap(m_map);

	//m_entities = Core::GetCore()->GetResources()->GetEntityList();
	m_entities.push_back("structures/gondor/castle_wall.json");
	m_entities.push_back("structures/gondor/barracks.json");
	m_entities.push_back("units/isengard/urukhai_crossbow.json");
	m_entity = Core::GetCore()->GetResources()->GetEntity("entities/" + m_entities[m_entity_index]);
	m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
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

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_UP))
	{
		m_instance->SetHealth(0);
		m_entity_index = (m_entity_index + 1) % m_entities.size();
		m_entity = Core::GetCore()->GetResources()->GetEntity("entities/" + m_entities[m_entity_index]);
		m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
	}

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_DOWN))
	{
		m_instance->SetHealth(0);
		m_entity_index = (m_entity_index - 1);
		if (m_entity_index == -1)
			m_entity_index = m_entities.size() - 1;
		m_entity = Core::GetCore()->GetResources()->GetEntity("entities/" + m_entities[m_entity_index]);
		m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
	}

	glm::vec3 mouse_position;
	if (!m_map->GetTerrain()->GetMousePositionInWorldSpace(Core::GetCore()->GetInput()->GetMousePosition(), mouse_position))
		mouse_position = m_old_mouse_position;

	m_instance->SetPosition(mouse_position);

	if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		glm::vec3 position;
		if (m_map->GetTerrain()->GetMousePositionInWorldSpace(Core::GetCore()->GetInput()->GetMousePosition(), position))
		{
			//m_map->GetTerrain()->SetHeight(position, 10.0f, 3);
			//m_map->GetTerrain()->SetMaterial(position, 10.0f, 0);
		}
	}

	if (Core::GetCore()->GetInput()->MouseButtonJustReleased(GLFW_MOUSE_BUTTON_1))
	{
		m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
	}

	if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_2))
	{
		m_camera->Move(Core::GetCore()->GetInput()->GetMouseDelta());
	}
	else if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_3))
		m_camera->Rotate(Core::GetCore()->GetInput()->GetMouseDelta().x);

	m_camera->Zoom(Core::GetCore()->GetInput()->GetMouseWheelDeltaY());

	m_old_mouse_position = mouse_position;
}