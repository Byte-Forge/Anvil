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
		/**
		 * @fn	inline const std::string GetCwd()
		 *
		 * @brief	Gets the cwd.
		 *
		 * @return	The cwd.
		 */
		inline const std::string GetCwd()
		{
			char buffer[1024];
			getcwd(buffer, 1024);
			return buffer;
		}

		/**
		 * @fn	std::vector<std::string> ListFiles(const std::string& dir, const std::string& ext = "");
		 *
		 * @brief	List files.
		 *
		 * @param	dir	The dir.
		 * @param	ext	The extent.
		 *
		 * @return	A std::vector&lt;std::string&gt;
		 */
		std::vector<std::string> ListFiles(const std::string& dir, const std::string& ext = "");		

		std::vector<std::string> ListFilesRecursively(const std::string& dir, const std::string& ext = "");
	}

	/**
	 * @fn	void ShowError(const std::string& msg);
	 *
	 * @brief	Shows the error.
	 *
	 * @param	msg	The message.
	 */
	void ShowError(const std::string& msg);
}