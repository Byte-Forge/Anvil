/*
************************************
* Copyright (C) 2016 ByteForge
* MaterialLoader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	class MaterialLoader
	{
	public:
		static void LoadMaterial(const std::string &name, const std::string &path);
	};
}