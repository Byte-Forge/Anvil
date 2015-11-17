//
// Created by stephan on 11.11.15.
//

#include "ResourceHandler.hpp"

using namespace hpse;
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

	template<class IResource>
	std::shared_ptr<IResource> ResourceHandler::GetResource(const std::string &name)
	{
		if (m_resources.count(name) == 0)
		{
			IResource.Load(name);
		}
		if (m_resources.count(name) == 0)
		{
			cout << "no such resource found: " << name << endl;
			return nullptr;
		}
		return m_resources[name];
	}

	void ResourceHandler::AddResource(std::string & name, std::shared_ptr<IResource> resource)
	{
		m_resources.insert({ name, resource });
	}
}

