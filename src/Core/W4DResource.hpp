#pragma once
#include <string>
#include "IResource.hpp"
#include "../Loaders/W4DLoader.hpp"


namespace hpse
{
    class W4DResource : public IResource
    {
		void Load(const std::string& file); 
    };
}