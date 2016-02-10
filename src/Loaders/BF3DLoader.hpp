/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	class BF3DLoader
	{
	public:
		static void Load(const std::string& name, const std::string& path);
	};
}