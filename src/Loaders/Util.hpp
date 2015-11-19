#pragma once
#include <string>
#include <algorithm>
#include <glm/glm.hpp>
#include <fstream>

namespace hpse
{
	inline long getFStreamSize(std::ifstream& file)
	{
		file.seekg(0, std::ios::end);
		long size = file.tellg();
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
}