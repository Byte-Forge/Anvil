/*
************************************
* Copyright (C) 2016 ByteForge
* JsonLoader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	class JsonLoader
	{
	public:
		static void LoadMaterial(const std::string &name, const std::string &path);
		static void LoadEntity(const std::string &name, const std::string &path);
	};
}