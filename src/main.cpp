#include "Core.hpp"
#include "Environment.hpp"
#include <include/cef_app.h>

int main(int argc, char** argv) 
{
	//Chromium Embedded Framework init code
	#ifdef _WIN32
	CefMainArgs args(GetModuleHandle(NULL));
	#else
	CefMainArgs args(argc, argv);
	#endif

	int exit_code = CefExecuteProcess(args, nullptr,NULL);
	if (exit_code >= 0)
	{
		// The sub-process terminated, exit now.
		return exit_code;
	}

	CefSettings settings;
	settings.no_sandbox = true;
	settings.windowless_rendering_enabled = true;
	settings.command_line_args_disabled = true;
	settings.remote_debugging_port = 8080;
	settings.log_severity = LOGSEVERITY_DISABLE;
	CefInitialize(args, settings, nullptr, NULL);

	Environment::Args = std::vector<std::string>(argv, argv + argc);
	Environment::Argc = argc;
	Environment::Argv = argv;

	{
		hpse::Core engine;

		engine.Run();
	}

	CefShutdown();
	return 0;
}