//
// Created by stephan on 11.11.15.
//

#include "ResourceHandler.hpp"

using namespace hpse;

std::shared_ptr<IResource> ResourceHandler::GetResource(const std::string &name)
{
    return m_resources[name];
}