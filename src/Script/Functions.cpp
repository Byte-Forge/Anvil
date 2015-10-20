#include "../Core.hpp"
using namespace hpse;

extern "C" void LoadGUI(const char * name)
{
	auto& gui  = Core::GetGUI();
	gui->LoadFile(name);
}
