//
// Created by stephan on 11.11.15.
//
#include <string>
#include <memory>
#include <map>
#include "IResource.hpp"
#pragma once

namespace hpse
{
    class ResourceHandler
    {
    public:
        std::shared_ptr<IResource> GetResource(const std::string& name);

    private:
        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
    };
}


