#pragma once 
#include <string>

#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning

#elif
#include <unistd.h>
#endif


namespace hpse
{
	namespace IO
	{
		inline const std::string GetCwd()
		{
			char buffer[1024];
			getcwd(buffer, 1024);
			return buffer;
		}
	}
}