/*
************************************
* Copyright (C) 2016 ByteForge
* ScriptInterface.hpp
************************************
*/

#pragma once

struct lua_State;

namespace anvil
{
	class ScriptInterface
	{
	public:
		void Initialise(lua_State*);
	};
}