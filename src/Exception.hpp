/*
************************************
* Copyright (C) 2016 ByteForge
* Exception.hpp
************************************
*/

#pragma once
#include <exception>
#include <string>

/**
 * @class	AnvilException
 *
 * @brief	Exception for signalling anvil errors and to shut down the engine
 */
class AnvilException : public std::exception
{
public:

	/**
	 * @fn	AnvilException::AnvilException(const std::string& msg,const char* file, int line);
	 *
	 * @brief	Constructor.

	 * @param	msg 	The message to display.
	 * @param	file	The file where the error occured.
	 * @param	line	The line in the file of the error.
	 */
	AnvilException(const std::string& msg,const char* file, int line);

	/**
	 * @fn	virtual const char* AnvilException::what() const throw();
	 *
	 * @brief	Gets the what.
	 *
	 * @return	null if it fails, else a char*.
	 */
	virtual const char* what() const throw();

private:
	std::string m_message;
};