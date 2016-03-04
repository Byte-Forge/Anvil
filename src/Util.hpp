/*
************************************
* Copyright (C) 2016 ByteForge
* Util.hpp
************************************
*/

#pragma once
#include <string>
#include <algorithm>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>
#include <sstream>

namespace anvil
{
	/**
	 * @fn	inline long getFStreamSize(std::ifstream& file)
	 *
	 * @brief	Gets f stream size.
	 *
	 * @param [in,out]	file	The file.
	 *
	 * @return	The f stream size.
	 */
	inline long getFStreamSize(std::ifstream& file)
	{
		file.seekg(0, std::ios::end);
		long size = (long)file.tellg();
		file.seekg(0, std::ios::beg);
		return size;
	}

	/**
	 * @fn	template<class T> inline T read(std::ifstream& fin)
	 *
	 * @brief	Reads the given fin.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	fin	The fin.
	 *
	 * @return	A T.
	 */
	template<class T>
	inline T read(std::ifstream& fin)
	{
		T result;
		fin.read((char*)&result, sizeof(T));
		return result;
	}

	/**
	 * @fn	template<typename T> inline void readArray(std::ifstream& fin, const unsigned int chunksize, T*& arr)
	 *
	 * @brief	Reads an array.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	fin	The fin.
	 * @param	chunksize  	The chunksize.
	 * @param [in,out]	arr	[in,out] If non-null, the array.
	 */
	template<typename T>
	inline void readArray(std::ifstream& fin, const unsigned int chunksize, T*& arr)
	{
		auto num_elements = chunksize / sizeof(T);
		arr = new T[num_elements];

		fin.read((char*)arr, sizeof(T)*num_elements);
	}

	/**
	 * @fn	template<typename T> inline std::vector<T> readVector(std::ifstream& fin, const unsigned int chunksize)
	 *
	 * @brief	Reads a vector.
	 *
	 * @tparam	T	Generic type parameter.
	 * @param [in,out]	fin	The fin.
	 * @param	chunksize  	The chunksize.
	 *
	 * @return	The vector.
	 */
	template<typename T>
	inline std::vector<T> readVector(std::ifstream& fin, const unsigned int chunksize)
	{
		std::vector<T> result;
		auto num_elements = chunksize / sizeof(T);
		result.resize(num_elements);

		fin.read((char*)&result[0], sizeof(T)*num_elements);
		return result;
	}

	/**
	 * @fn	inline std::string readString(std::ifstream& fin)
	 *
	 * @brief	Reads a string.
	 *
	 * @param [in,out]	fin	The fin.
	 *
	 * @return	The string.
	 */
	inline std::string readString(std::ifstream& fin)
	{
		std::string result;
		char c;
		while ((c = fin.get()))
			result.push_back(c);
		return result;
	}

	/**
	 * @fn	inline std::string toUpper(const std::string& str)
	 *
	 * @brief	Converts a str to an upper.
	 *
	 * @param	str	The string.
	 *
	 * @return	str as a std::string.
	 */
	inline std::string toUpper(const std::string& str)
	{
		std::string upper = str;
		std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
		return upper;
	}

	/**
	 * @fn	inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	 *
	 * @brief	Splits.
	 *
	 * @param	s			 	The std::string to process.
	 * @param	delim		 	The delimiter.
	 * @param [in,out]	elems	The elements.
	 *
	 * @return	A std::vector&lt;std::string&gt;&amp;
	 */
	inline std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
		{
			elems.push_back(item);
		}
		return elems;
	}

	/**
	 * @fn	inline std::vector<std::string> split(const std::string &s, char delim)
	 *
	 * @brief	Splits.
	 *
	 * @param	s	 	The std::string to process.
	 * @param	delim	The delimiter.
	 *
	 * @return	A std::vector&lt;std::string&gt;
	 */
	inline std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	/**
	 * @fn	inline bool fileExists(const std::string& str)
	 *
	 * @brief	Queries if a given file exists.
	 *
	 * @param	str	The string.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */
	inline bool fileExists(const std::string& str)
	{
		std::fstream fin(str);
		return !fin.fail();
	}
}