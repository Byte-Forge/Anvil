/*
************************************
* Copyright (C) 2016 ByteForge
* Environment.hpp
************************************
*/

#pragma once
#include <vector>
#include <string>

/**
 * @class	Environment
 *
 * @brief	Handles the command line parameters.
 */
class Environment
{
public:
	static std::vector<std::string> Args;
	static int Argc;
	static char** Argv;
};