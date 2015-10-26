#include "Core.hpp"
#include "Environment.hpp"
#include <include/cef_app.h>

int main(int argc, char** argv) 
{
	Environment::Args = std::vector<std::string>(argv, argv + argc);
	Environment::Argc = argc;
	Environment::Argv = argv;

	#ifdef _WIN32
	CefMainArgs args(GetModuleHandle(NULL));
	#else
	CefMainArgs args(Environment::Argc, Environment::Argv);
	#endif

	int exit_code = CefExecuteProcess(args, nullptr,NULL);
	if (exit_code >= 0) {
	// The sub-process terminated, exit now.
	return exit_code;
	}

	hpse::Core engine;

	engine.Run();
	return 0;
}