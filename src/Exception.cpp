#include "Exception.hpp"

HpseException::HpseException(const std::string& msg, const char* file, int line)
{
	m_message = "HPSE EXCEPTION:\n"
		"FILE: " + std::string(file) + "\n"
		"LINE: " + std::to_string(line) + "\n"
		"MESSAGE: " + msg;
}

const char* HpseException::what() const throw ()
{
	return m_message.c_str();
}