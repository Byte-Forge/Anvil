#include "../Core.hpp"
#include "../Graphics/IRenderer.hpp"
using namespace hpse;

#ifdef _MSC_VER 
#define SCRIPT_FUNC __declspec(dllexport)
#elif
#define SCRIPT_FUNC
#endif

extern "C"
{
	SCRIPT_FUNC void LoadGUI(const char * name)
	{
		auto& gui = Core::GetGUI();
		gui->LoadFile(name);
	}

	SCRIPT_FUNC void PrintRenderer()
	{
		auto renderer = Core::GetGraphics()->GetRenderer();
		renderer->PrintInfo();
	}
}
