#include "ScriptInterface.hpp"
#include <Rocket/Core/Factory.h>
#include <Rocket/Core/Lua/LuaType.h>
#include <Rocket/Core/Lua/lua.hpp>
#include "../Core.hpp"
using namespace hpse;

int GameShutdown(lua_State* L);
int GameGetFPS(lua_State* L);


void ScriptInterface::Initialise(lua_State * L)
{
	luaL_dostring(L, "Game = Game or {}"); //doing this in Lua because it would be 10+ lines in C++
	lua_getglobal(L, "Game");
	int game = lua_gettop(L);

	if (lua_isnil(L, game))
	{
		Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Error creating the Game table from C++ in ScriptInterface::Initialise");
		return;
	}

	lua_pushcfunction(L, GameShutdown);
	lua_setfield(L, game, "Shutdown");

	lua_pushcfunction(L, GameGetFPS);
	lua_setfield(L, game, "GetFPS");

	lua_pop(L, 1); //pop Game
}

int GameShutdown(lua_State* L)
{
	Core::GetCore()->Quit();
	return 0;
}

int GameGetFPS(lua_State* L)
{
	lua_pushnumber(L, 60);
	return 1;
}