#include "EntityLoader.hpp"
#include "../Core.hpp"
#include "../Objects/Entity.hpp"
#include "../Loaders/Util.hpp"
#include <memory>

using namespace hpse;

void EntityLoader::LoadEntity(const std::string &name, const std::string &path)
{
	std::shared_ptr<Entity> ent = std::make_shared<Entity>();
	ent->Load(path);
	Core::GetCore()->GetResources()->AddResource(toUpper(name), ent);
}