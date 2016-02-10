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