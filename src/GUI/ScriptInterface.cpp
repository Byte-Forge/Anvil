/*
************************************
* Copyright (C) 2016 ByteForge
* ScriptInterface.cpp
************************************
*/

#include "ScriptInterface.hpp"
#include <Rocket/Core/Factory.h>
#include <Rocket/Core/Lua/LuaType.h>
#include <Rocket/Core/Lua/lua.hpp>
#include "../Core.hpp"
#include "../Util/FPS.hpp"
#include "../Types/Map.hpp"
#include "../Graphics.hpp"

using namespace anvil;

int GameShutdown(lua_State* L);
int GameGetFPS(lua_State* L);
int GameGetPolygons(lua_State* L);
int GameGetGPUName(lua_State* L);
int GameGetTotalVRAM(lua_State* L);
int GameGetUsedVRAM(lua_State* L);

void ScriptInterface::Initialise(lua_State * L)
{
	luaL_dostring(L, "Game = Game or {}"); //doing this in Lua because it would be 10+ lines in C++
	lua_getglobal(L, "Game");
	int game = lua_gettop(L);

	if (lua_isnil(L, game))
	{
		Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Error creating the Game table from C++ in ScriptInterface::Initialise()");
		return;
	}

	lua_pushcfunction(L, GameShutdown);
	lua_setfield(L, game, "Shutdown");

	lua_pushcfunction(L, GameGetFPS);
	lua_setfield(L, game, "GetFPS");

	lua_pushcfunction(L, GameGetPolygons);
	lua_setfield(L, game, "GetPolygons");

	lua_pushcfunction(L, GameGetGPUName);
	lua_setfield(L, game, "GetGPUName");

	lua_pushcfunction(L, GameGetUsedVRAM);
	lua_setfield(L, game, "GetUsedVRAM");

	lua_pushcfunction(L, GameGetTotalVRAM);
	lua_setfield(L, game, "GetTotalVRAM");

	lua_pop(L, 1); //pop Game
}

int GameShutdown(lua_State* L)
{
	Core::GetCore()->Quit();
	return 0;
}

int GameGetFPS(lua_State* L)
{
	double fps = Core::GetCore()->GetFPS().GetFPS();
	lua_pushnumber(L,fps);
	return 1;
}

int GameGetPolygons(lua_State* L)
{
	int polyCount = 0;
	auto& renderer = Core::GetCore()->GetGraphics()->GetRenderer();
	if (renderer)
		polyCount = renderer->GetRenderedPolygons();

	lua_pushnumber(L, polyCount);
	return 1;
}

int GameGetGPUName(lua_State* L)
{
	auto name = Core::GetCore()->GetGraphics()->GetRenderer()->GetGPUName();
	lua_pushstring(L, name.c_str());
	return 1;
}

int GameGetTotalVRAM(lua_State* L)
{
	int vram = Core::GetCore()->GetGraphics()->GetRenderer()->GetTotalVRAM();
	lua_pushnumber(L, vram);
	return 1;
}

int GameGetUsedVRAM(lua_State* L)
{
	int vram = Core::GetCore()->GetGraphics()->GetRenderer()->GetUsedVRAM();
	lua_pushnumber(L, vram);
	return 1;
}
