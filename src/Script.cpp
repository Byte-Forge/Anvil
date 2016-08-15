/*
************************************
* Copyright (C) 2016 ByteForge
* Script.cpp
************************************
*/

#include "Script.hpp"
#include "Environment.hpp"
#include <fstream>
#include <iostream>
#include "Util/Logger.hpp"

using namespace anvil;

static int l_my_print(lua_State* L) 
{
    int nargs = lua_gettop(L);

    for (int i=1; i <= nargs; ++i) {
		Logger::Print(lua_tostring(L, i));
    }
    std::cout << std::endl;

    return 0;
}

static const struct luaL_Reg printlib [] = 
{
  {"print", l_my_print},
  {NULL, NULL} /* end of array */
};


Script::Script()
{
	m_state = luaL_newstate();  //crash on mac, maybe lua as dynamic build
	luaL_openlibs(m_state);
	lua_getglobal(m_state, "_G");
	luaL_register(m_state, NULL, printlib);
	lua_pop(m_state, 1);
}

Script::~Script()
{
	lua_close(m_state);
}

void Script::Update()
{
	
}

void Script::LoadFile(const std::string& file)
{
	if (luaL_dofile(m_state, file.c_str()))
	{
		std::cout << lua_tostring(m_state, -1) << std::endl;
	}
}
	
void Script::RunString(const std::string& file)
{
	if (luaL_dostring(m_state, file.c_str()))
	{
		std::cout << lua_tostring(m_state, -1) << std::endl;
	}
}
	