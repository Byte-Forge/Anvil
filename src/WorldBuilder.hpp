/*
************************************
* Copyright (C) 2016 ByteForge
* WorldBuilder.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace anvil
{
	class Map;
	class Camera;

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
		std::shared_ptr<Map> m_map;
		std::shared_ptr<Camera> m_camera;
	};
}