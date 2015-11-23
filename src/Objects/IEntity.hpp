//
// Created by michael on 19.11.15.
//
#pragma once
#include <string>
#include <map>
#include "ConditionState.hpp"
#include "../Core/IResource.hpp"


namespace hpse
{
    class IEntity : public IResource
    {
	private:
		std::string name;
    };
}


