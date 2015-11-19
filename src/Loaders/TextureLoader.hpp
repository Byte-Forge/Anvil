#pragma once
#include <fstream>
#include <iostream>

using namespace std;

namespace hpse
{
	class TextureLoader
	{
	public:
		static void Load(const std::string& name);
	};
}