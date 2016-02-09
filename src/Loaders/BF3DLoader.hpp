#pragma once
#include <string>

namespace hpse
{
	class BF3DLoader
	{
	public:
		static void Load(const std::string& name, const std::string& path);
	};
}