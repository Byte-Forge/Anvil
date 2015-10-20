#include "Script.hpp"
#include "Environment.hpp"
#include <fstream>
#include <iostream>
using namespace hpse;

Script::Script()
{
	m_state = luaL_newstate();
	luaL_openlibs(m_state);

	if (luaL_dofile(m_state, "./script/binding.lua"))
	{
		std::cout << lua_tostring(m_state, -1) << std::endl;
	}
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
	