/*
************************************
* Copyright (C) 2016 ByteForge
* Exception.hpp
************************************
*/

#pragma once
#include <exception>
#include <string>

class AnvilException : public std::exception
{
public:
	AnvilException(const std::string& msg,const char* file, int line);
	virtual const char* what() const throw();
private:
	std::string m_message;
};