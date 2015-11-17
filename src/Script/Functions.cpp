#include "../Core.hpp"
#include "../Graphics/IRenderer.hpp"

using namespace hpse;

extern "C" void LoadGUI(const char * name)
{
	auto& gui  = Core::GetGUI();
	gui->LoadFile(name);
}

extern "C" void PrintRenderer()
{
	auto renderer = Core::GetGraphics()->GetRenderer();
	renderer->PrintInfo();
}