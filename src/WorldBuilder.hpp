/*
************************************
* Copyright (C) 2016 ByteForge
* WorldBuilder.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <string>

#define MAX_BRUSH_WIDTH 30

namespace anvil
{
	class Map;
	class Camera;
	class Entity;
	class Instance;

	/**
	 * @class	WorldBuilder
	 *
	 * @brief	A world builder.
	 */
	class WorldBuilder
	{
	public:

		enum MODE
		{
			HEIGHT,
			TEXTURE,
			ENTITY
		};

		/**
		 * @fn	WorldBuilder::WorldBuilder();
		 *
		 * @brief	Default constructor.
		 */
		WorldBuilder();

		/**
		 * @fn	WorldBuilder::~WorldBuilder();
		 *
		 * @brief	Destructor.
		 */
		~WorldBuilder();

		void Update();

		inline void DecreaseBrushWidth() { if (m_brush_width > 1) m_brush_width--; }
		inline void IncreaseBrushWidth() { if (m_brush_width < MAX_BRUSH_WIDTH) m_brush_width++; }

		inline void DecreaseBrushHeight() { m_brush_height--; }
		inline void IncreaseBrushHeight() { m_brush_height++; }

		inline void SetTerrainMode() { m_mode = HEIGHT; }
		inline void SetTextureMode() { m_mode = TEXTURE; }
		inline void SetEntityMode() { m_mode = ENTITY; }

	private:
		void UpdateUserInput();

	private:
		MODE m_mode;
		glm::vec3 m_old_mouse_position;

		int m_brush_height = 2;
		int m_brush_width = 20;
		int m_brush_material = 0;

		size_t m_entity_index = 0;
		std::vector<std::string> m_entities;
		std::shared_ptr<Entity> m_entity;
		std::shared_ptr<Instance> m_instance;


		std::shared_ptr<Map> m_map;
		std::shared_ptr<Camera> m_camera;
	};
}