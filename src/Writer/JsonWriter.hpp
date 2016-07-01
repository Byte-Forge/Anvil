/*
************************************
* Copyright (C) 2016 ByteForge
* JsonWriter.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	/**
	 * @class	JsonWriter
	 *
	 * @brief	A JSON writer.
	 */
	class JsonWriter
	{
	public:

		/**
		* @fn	static void JsonWriter::SaveOptions(const std::string& path);
		*
		* @brief	Write the engine options to file
		*
		* @param	path	Full pathname of the optionsfile.
		*/
		static void SaveOptions(const std::string& path);
		
	};
}