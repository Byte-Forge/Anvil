#include "Core.hpp"
#include "Environment.hpp"
#include "Util/Platform.hpp"
#include "Exception.hpp"
#include <iostream>

int main(int argc, char** argv) 
{

	Environment::Args = std::vector<std::string>(argv, argv + argc);
	Environment::Argc = argc;
	Environment::Argv = argv;


	try
	{
	hpse::Core engine;
	engine.Run();
	}
	catch(const HpseException& e)
	{
		hpse::ShowError(e.what());
		return -1;
	}
	

	return 0;
}