/*
************************************
* Copyright (C) 2016 ByteForge
* Platform.hpp
************************************
*/

#pragma once 
#include <string>
#include <vector>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
#include <unistd.h>
#endif


namespace anvil
{
	namespace IO
	{
		inline const std::string GetCwd()
		{
			char buffer[1024];
			getcwd(buffer, 1024);
			return buffer;
		}

		std::vector<std::string> ListFiles(const std::string& dir, const std::string& ext = "");		
	}

	void ShowError(const std::string& msg);
}