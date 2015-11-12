#pragma once
#include <fstream>
#include "../Core/IResource.hpp"

using namespace std;

namespace hpse
{
	class W4DLoader
	{
	public:
		IResource Load(const char * name);
	};
}