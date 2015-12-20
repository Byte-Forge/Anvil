#include "Core.hpp"
#include "Environment.hpp"
#include <iostream>

int main(int argc, char** argv) 
{

	Environment::Args = std::vector<std::string>(argv, argv + argc);
	Environment::Argc = argc;
	Environment::Argv = argv;

	{
		hpse::Core engine;

		engine.Run();
	}

	return 0;
}