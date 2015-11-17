#pragma once
#include "../src/Core/IResource.hpp"
#include "../src/Loaders/W4DLoader.hpp"

using namespace hpse;

class W4DResource : IResource
{
	bool Load(const std::string& file) {
		W4DLoader.Load(file);
	}
};

