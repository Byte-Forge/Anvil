/*
************************************
* Copyright (C) 2016 ByteForge
* StringHelper.hpp
************************************
*/

#pragma once
#include <vector>
#include <sstream>

namespace anvil
{
	namespace StringHelper
	{
		std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) 
		{
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim)) 
			{
				elems.push_back(item);
			}
			return elems;
		}


		std::vector<std::string> split(const std::string &s, char delim) 
		{
			std::vector<std::string> elems;
			split(s, delim, elems);
			return elems;
		}
	}
}