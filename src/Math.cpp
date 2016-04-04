/*
************************************
* Copyright (C) 2016 ByteForge
* Math.cpp
************************************
*/

#include "Math.hpp"

using namespace anvil;

glm::vec3  Math::ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c)
{
	return glm::normalize(glm::cross(c - b, a - b));
}

