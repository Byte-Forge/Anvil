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
	class Script
	{
	public:
		Script();
		~Script();

		void Update();
		void LoadFile(const std::string& file);
		inline lua_State* GetState()
		{
			return m_state;
		}
	private:
		lua_State* m_state;
	};
}