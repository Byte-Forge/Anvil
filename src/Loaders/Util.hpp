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

namespace anvil
{
	inline long getFStreamSize(std::ifstream& file)
	{
		file.seekg(0, std::ios::end);
		long size = (long)file.tellg();
		file.seekg(0, std::ios::beg);
		return size;
	}

	template<class T>
	inline T read(std::ifstream& fin)
	{
		T result;
		fin.read((char*)&result, sizeof(T));
		return result;
	}

	//Read an array of a type 
	template<typename T>
	inline void readArray(std::ifstream& fin, const unsigned int chunksize, T*& arr)
	{
		auto num_elements = chunksize / sizeof(T);
		arr = new T[num_elements];

		fin.read((char*)arr, sizeof(T)*num_elements);
	}

	template<typename T>
	inline std::vector<T> readVector(std::ifstream& fin, const unsigned int chunksize)
	{
		std::vector<T> result;
		auto num_elements = chunksize / sizeof(T);
		result.resize(num_elements);

		fin.read((char*)&result[0], sizeof(T)*num_elements);
		return result;
	}

	inline std::string readString(std::ifstream& fin)
	{
		std::string result;
		char c;
		while ((c = fin.get()))
			result.push_back(c);
		return result;
	}

	inline std::string toUpper(const std::string& str)
	{
		std::string upper = str;
		std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
		return upper;
	}

	inline bool fileExists(const std::string& str)
	{
		std::fstream fin(str);
		return !fin.fail();
	}
}