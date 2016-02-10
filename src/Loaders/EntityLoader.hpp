/*
************************************
* Copyright (C) 2016 ByteForge
* EntityLoader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	class EntityLoader
	{
	public:
		static void LoadEntity(const std::string &name, const std::string &path);
	};
}