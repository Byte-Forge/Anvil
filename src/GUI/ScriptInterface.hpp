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
	/**
	 * @class	ScriptInterface
	 *
	 * @brief	A script interface.
	 */
	class ScriptInterface
	{
	public:

		/**
		 * @fn	void ScriptInterface::Initialise(lua_State*);
		 *
		 * @brief	Initialises this object.
		 *
		 * @param [in,out]	parameter1	If non-null, the first parameter.
		 */
		void Initialise(lua_State*);
	};
}