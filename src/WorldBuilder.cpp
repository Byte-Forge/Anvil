/*
************************************
* Copyright (C) 2016 ByteForge
* WorldBuilder.cpp
************************************
*/

#include "WorldBuilder.hpp"
#include "Util.hpp"
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

	m_mode = HEIGHT;

	//Core::GetCore()->GetResources()->GetEntityList();
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
	glm::vec3 mouse_position;
	if (!m_map->GetTerrain()->GetMousePositionInWorldSpace(Core::GetCore()->GetInput()->GetMousePosition(), mouse_position))
		mouse_position = m_old_mouse_position;

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_F1))
		m_mode = HEIGHT;
	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_F2))
		m_mode = TEXTURE;
	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_F3))
		m_mode = ENTITY;


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
		if (m_mode == HEIGHT)
		{
			m_brush_height++;
		}
		else if (m_mode == ENTITY)
		{
			m_instance->SetInvalid();
			m_entity_index = (m_entity_index + 1) % m_entities.size();
			m_entity = Core::GetCore()->GetResources()->GetEntity("entities/" + m_entities[m_entity_index]);
			m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
		}
	}

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_DOWN))
	{
		if (m_mode == HEIGHT)
		{
			m_brush_height--;
		}
		else if (m_mode == ENTITY)
		{
			m_instance->SetInvalid();
			m_entity_index = (m_entity_index - 1);
			if (m_entity_index == -1)
				m_entity_index = m_entities.size() - 1;
			m_entity = Core::GetCore()->GetResources()->GetEntity("entities/" + m_entities[m_entity_index]);
			m_instance = m_entity->AddInstance(glm::vec3(0.0, -10.0, 0.0));
		}
	}

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_RIGHT_BRACKET)) // * + ~ key
	{
		if (m_brush_width < 30)
			m_brush_width++;
	}

	if (Core::GetCore()->GetInput()->KeyJustReleased(GLFW_KEY_SLASH)) // - _ key
	{
		if (m_brush_width > 1)
			m_brush_width--;
	}

	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_PAGE_UP))
	{
		if (m_mode == HEIGHT)
		{
			
		}
		else if (m_mode == ENTITY)
		{
			m_instance->Rotate(0.2f, glm::vec3(0.0, 1.0, 0.0));
		}
	}
	if (Core::GetCore()->GetInput()->KeyPressed(GLFW_KEY_PAGE_DOWN))
	{
		if (m_mode == HEIGHT)
		{
			
		}
		else if (m_mode == ENTITY)
		{
			m_instance->Rotate(-0.2f, glm::vec3(0.0, 1.0, 0.0));
		}
	}

	if (Core::GetCore()->GetInput()->MouseButtonReleased(GLFW_MOUSE_BUTTON_1))
	{
		if (m_mode == HEIGHT)
		{

		}
		else if (m_mode == ENTITY)
		{
			m_instance->SetPosition(mouse_position);
		}
	}

	if (Core::GetCore()->GetInput()->MouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	{
		if (m_mode == HEIGHT)
		{
			m_map->GetTerrain()->SetHeight(mouse_position, m_brush_width, m_brush_height);
		}
		else if (m_mode == TEXTURE)
		{
			m_map->GetTerrain()->SetMaterial(mouse_position, m_brush_width, m_brush_material);
		}
		else if (m_mode == ENTITY)
		{
			//set rotation not direction
			//m_instance->SetDirection(glm::normalize(m_instance->GetPosition() - mouse_position));
		}
	}

	if (Core::GetCore()->GetInput()->MouseButtonJustReleased(GLFW_MOUSE_BUTTON_1))
	{

		if (m_mode == HEIGHT)
		{

		}
		else if (m_mode == TEXTURE)
		{

		}
		else if (m_mode == ENTITY)
		{
			m_instance = m_entity->AddInstance(glm::vec3(mouse_position));
		}
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