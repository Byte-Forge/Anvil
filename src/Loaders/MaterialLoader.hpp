#pragma once
#include <string>
namespace hpse
{
	class MaterialLoader
	{
	public:
		static void LoadMaterial(const std::string &name, const std::string &path);
	};
}