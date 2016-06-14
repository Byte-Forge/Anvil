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
#include <iostream>
#include <fstream>
#include <vector>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <sstream>
#include <iomanip>

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
		std::ifstream fin(str);
		return fin.good(); //fin.close() is called by the destructor
	}

	/**
	* @fn	inline void printVec(glm::vec4 vec)
	*
	* @brief	prints the given vector
	*
	* @param	vec		the vector to be printed
	*/
	inline void printVec(glm::vec4 vec)
	{
		std::cout << std::fixed << std::setprecision(2) << vec[0] << "\t" << vec[1] << "\t" << vec[2] << "\t" << vec[3] << std::endl;
		std::cout << std::endl;
	}

	/**
	* @fn	inline void printVec4(glm::vec4 v)
	*
	* @brief	prints the given vec4
	*
	* @param	v	the vec4 to be printed
	*/
	inline void printVec4(glm::vec4 v)
	{
		std::cout << std::fixed << std::setprecision(2) << v.x << "\t" << v.y << "\t" << v.z << "\t" << v.w << std::endl;
		std::cout << std::endl;
	}

	/**
	* @fn	inline void printQuat(glm::quat q)
	*
	* @brief	prints the given quaternion
	*
	* @param	q	the quaternion to be printed
	*/
	inline void printQuat(glm::quat q)
	{
		std::cout << std::fixed << std::setprecision(2) << q.w << "\t" << q.x << "\t" << q.y << "\t" << q.z << std::endl;
		std::cout << std::endl;
	}

	/**
	* @fn	inline void printMat4x4(glm::mat4x4 mat)
	*
	* @brief	prints the given 4x4 matrix
	*
	* @param	mat		the matrix to be printed
	*/
	inline void printMat4x4(glm::mat4x4 mat)
	{
		std::cout << std::fixed << std::setprecision(2) << mat[0][0] << "\t" << mat[0][1] << "\t" << mat[0][2] << "\t" << mat[0][3] << std::endl;
		std::cout << std::fixed << std::setprecision(2) << mat[1][0] << "\t" << mat[1][1] << "\t" << mat[1][2] << "\t" << mat[1][3] << std::endl;
		std::cout << std::fixed << std::setprecision(2) << mat[2][0] << "\t" << mat[2][1] << "\t" << mat[2][2] << "\t" << mat[2][3] << std::endl;
		std::cout << std::fixed << std::setprecision(2) << mat[3][0] << "\t" << mat[3][1] << "\t" << mat[3][2] << "\t" << mat[3][3] << std::endl;
		std::cout << std::endl;
	}
}