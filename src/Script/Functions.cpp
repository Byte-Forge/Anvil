#include <string>
#include <iostream>
#include "../Core.hpp"
#include "../Graphics/IRenderer.hpp"

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
		auto& gui = Core::GetCore()->GetGUI();
		gui->LoadFile(name);
	}

	SCRIPT_FUNC void LoadGUIByURL(const char* name)
	{
		auto& gui = Core::GetCore()->GetGUI();
		gui->LoadURL(name);
	}

	SCRIPT_FUNC void PrintRenderer()
	{
		auto renderer = Core::GetCore()->GetGraphics()->GetRenderer();
		renderer->PrintInfo();
	}

	SCRIPT_FUNC void AddModDir(const char* dir)
	{
		
	}
}
