/*
************************************
* Copyright (C) 2016 ByteForge
* Exception.cpp
************************************
*/

#include "Exception.hpp"

AnvilException::AnvilException(const std::string& msg, const char* file, int line)
{
	m_message = "Anvil EXCEPTION:\n"
		"FILE: " + std::string(file) + "\n"
		"LINE: " + std::to_string(line) + "\n"
		"MESSAGE: " + msg;
}

const char* AnvilException::what() const throw ()
{
	return m_message.c_str();
}