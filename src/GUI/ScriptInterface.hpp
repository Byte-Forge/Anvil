#pragma once

struct lua_State;
namespace hpse
{
	class ScriptInterface
	{
	public:
		void Initialise(lua_State*);
	};
}