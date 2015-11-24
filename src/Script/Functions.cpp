#include <string>
#include <iostream>
#include "../Core.hpp"
#include "../Graphics/IRenderer.hpp"
#include "../Objects/Structure.hpp"
using namespace hpse;

#ifdef _MSC_VER 
#define SCRIPT_FUNC __declspec(dllexport)
#else
#define SCRIPT_FUNC
#endif

extern "C"
{
	SCRIPT_FUNC void LoadGUIByFile(const char* name)
	{
		auto& gui = Core::GetGUI();
		gui->LoadFile(name);
	}

	SCRIPT_FUNC void LoadGUIByURL(const char* name)
	{
		auto& gui = Core::GetGUI();
		gui->LoadURL(name);
	}

	SCRIPT_FUNC void PrintRenderer()
	{
		auto renderer = Core::GetGraphics()->GetRenderer();
		renderer->PrintInfo();
	}

	SCRIPT_FUNC void AddTextureDir(const char* dir)
	{

	}

	SCRIPT_FUNC void AddMapDir(const char* dir)
	{

	}

	SCRIPT_FUNC void AddModelDir(const char* dir)
	{
		std::cout << dir << std::endl;
	}
}
