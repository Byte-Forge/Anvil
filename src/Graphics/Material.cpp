#include "Material.hpp"
#include "../Util/tinyxml2.h"

using namespace hpse;
using namespace tinyxml2;

bool Material::Load(const std::string& path)
{
	XMLDocument doc;
	if (doc.LoadFile(path.c_str()))
	{
		XMLNode *pRoot = doc.FirstChild();
		if (pRoot == nullptr) return XML_ERROR_FILE_READ_ERROR;

		XMLElement *pElement = pRoot->FirstChildElement("material");
		if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

		const char * name = nullptr;

		name = pElement->Attribute("name");

		/*
		int iOutInt;
		eResult = pElement->QueryIntText(&iOutInt);
		XMLCheckResult(eResult);
		*/
		return true;
	}
	return false;
}