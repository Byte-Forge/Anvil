//
// Created by stephan on 11.11.15.
//
#include <iostream>
#include "ResourceHandler.hpp"
#include "W4DResource.hpp"

using namespace std;

namespace hpse
{
	static ResourceHandler* unique;

	ResourceHandler* ResourceHandler::instance()
	{
		if (unique == NULL)
			unique = new ResourceHandler();
		return unique;
	}

	std::shared_ptr<IResource> ResourceHandler::GetResource(const std::string &name, ResourceType type)
	{
		if (m_resources.count(name) == 0)
		{
			//search for the file in the subdirs
			cout << "searching for file: " << name << endl;
			//res.Load(name);
		}
		if (m_resources.count(name) > 0)
		{
			return m_resources[name];
		}
		cout << "no such resource found: " << name << endl;
		return nullptr;
	}

	void ResourceHandler::AddResource(std::string & name, std::shared_ptr<IResource> resource)
	{
		m_resources.insert({ name, resource });
	}
}

