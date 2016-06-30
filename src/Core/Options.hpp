/*
************************************
* Copyright (C) 2016 ByteForge
* Options.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
	/**
	* @class	Options
	*
	* @brief	options of the engine
	*/
	class Options
	{
	public:

		/**
		 * @fn	static bool Options::Load(const std::string& path);
		 *
		 * @brief	Loads the options from the given file.
		 *
		 * @param	path	The path to load.
		 *
		 * @return	returns false if the options should be saved afterwards
		 */
		static bool Load(const std::string& path);

		/**
		 * @fn	static void Options::Save(const std::string& path);
		 *
		 * @brief	Saves the options to a specific file
		 *
		 * @param	path	The path to save.
		 */
		static void Save(const std::string& path);

		/**
		 * @fn	static void Options::Default();
		 *
		 * @brief	Load the default options
		 */
		static void Default();

		static inline int GetTessfactor()		{ return s_tessFactor; }
		static inline unsigned int GetWidth()	{ return s_width; }
		static inline unsigned int GetHeight()	{ return s_height; }
		static inline bool GetFullscreen()		{ return s_fullscreen; }
		static inline int GetSampleFactor()		{ return s_sampleFactor; }

	private:
		static bool s_fullscreen;
		static unsigned int s_width;
		static unsigned int s_height;
		static int s_tessFactor;
		static int s_sampleFactor;
	};
}
