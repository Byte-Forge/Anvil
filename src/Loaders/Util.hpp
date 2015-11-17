#pragma once
#include <string>
#include <glm/glm.hpp>
#include "../Types/W4D.hpp"

using namespace std;

namespace hpse
{
	inline long getFStreamSize(ifstream& file)
	{
		file.seekg(0, ios::end);
		long size = file.tellg();
		file.seekg(0, ios::beg);
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
}