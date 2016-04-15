/*
************************************
* Copyright (C) 2016 ByteForge
* main.cpp
************************************
*/

#include "Core.hpp"
#include "Environment.hpp"
#include "Util/Platform.hpp"
#include "Exception.hpp"
#include <iostream>

/**
 * @fn	int main(int argc, char** argv)
 *
 * @brief	Main entry-point for this application.
 *
 * @param	argc	Number of command-line arguments.
 * @param	argv	Array of command-line argument strings.
 *
 * @return	Exit-code for the process - 0 for success, else an error code.
 */
int main(int argc, char** argv) 
{

	Environment::Args = std::vector<std::string>(argv, argv + argc);
	Environment::Argc = argc;
	Environment::Argv = argv;

	try
	{
		anvil::Core engine;
		engine.Run();
	}
	catch(const AnvilException& e)
	{
		anvil::ShowError(e.what());
		return -1;
	}
	return 0;
}