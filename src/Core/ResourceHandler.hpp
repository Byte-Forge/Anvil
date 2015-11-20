//
// Created by stephan on 11.11.15.
//
#pragma once
#include <string>
#include <memory>
#include <map>
#include "IResource.hpp"

namespace hpse
{
	enum ResourceType
	{
		audio,
		texture,
		w4d,
		model,
		entity,
	};

    class ResourceHandler
    {
    public:
		static ResourceHandler* instance();

        std::shared_ptr<IResource> GetResource(const std::string& name, ResourceType type);

		void AddResource(const std::string &name, std::shared_ptr<IResource> resource);

    private:
        std::map<const std::string, std::shared_ptr<IResource>> m_resources;
    };
}


