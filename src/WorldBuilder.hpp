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

	private:
		void UpdateUserInput();

	private:
		glm::vec3 m_old_mouse_position;

		int m_entity_index = 0;
		std::vector<std::string> m_entities;
		std::shared_ptr<Entity> m_entity;
		std::shared_ptr<Instance> m_instance;
		std::shared_ptr<Map> m_map;
		std::shared_ptr<Camera> m_camera;
	};
}