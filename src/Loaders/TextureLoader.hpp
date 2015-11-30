#pragma once
#include <fstream>
#include <iostream>

namespace hpse
{
	class TextureLoader
	{
	public:
		static void Load(const std::string& name);
	};
}