#include "MaterialLoader.hpp"
#include "../Graphics/Material.hpp"
#include "../Core.hpp"
#include "../Loaders/Util.hpp"

using namespace hpse;

void MaterialLoader::LoadMaterial(const std::string &name, const std::string &path)
{
	std::shared_ptr<Material> mat = std::make_shared<Material>();
	mat->Load(path);
	Core::GetCore()->GetResources()->AddResource(toUpper(name), mat);
}
