/*
************************************
* Copyright (C) 2016 ByteForge
* Script.hpp
************************************
*/

#pragma once
#include <memory>
#include <string>
#include <lua.hpp>

namespace anvil
{
	/**
	 * @class	Script
	 *
	 * @brief	A script.
	 */
	class Script
	{
	public:

		/**
		 * @fn	Script::Script();
		 *
		 * @brief	Default constructor.
		 */
		Script();

		/**
		 * @fn	Script::~Script();
		 *
		 * @brief	Destructor.
		 */
		~Script();

		/**
		 * @fn	void Script::Update();
		 *
		 * @brief	Updates this object.
		 */
		void Update();

		/**
		 * @fn	void Script::LoadFile(const std::string& file);
		 *
		 * @brief	Loads a file.
		 *
		 * @param	file	The file.
		 */
		void LoadFile(const std::string& file);

		inline lua_State* GetState() { return m_state; }

	private:
		lua_State* m_state;
	};
}