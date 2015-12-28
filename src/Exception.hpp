#pragma once
#include <exception>
#include <string>

class HpseException : public std::exception
{
public:
	HpseException(const std::string& msg,const char* file, int line);
	virtual const char* what() const throw();
private:
	std::string m_message;
};