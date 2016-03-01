/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.hpp
************************************
*/

#pragma once
#include <string>
#include "../Graphics/IMesh.hpp"

namespace anvil
{
	class BF3DLoader
	{
	public:
		static void Load(const std::string& name, const std::string& path);
	private:
		static void LoadHierarchy(std::string name, std::ifstream& file, std::uint32_t chunkEnd);
		static void LoadModel(std::string name, std::ifstream& file, std::uint32_t chunkEnd);
		static void LoadMesh(std::ifstream& file, std::uint32_t chunkEnd);
	};
}