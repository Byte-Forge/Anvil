#pragma once
#include <string>

namespace hpse
{
	class EntityLoader
	{
	public:
		static void LoadEntity(const std::string &name, const std::string &path);
	};
}