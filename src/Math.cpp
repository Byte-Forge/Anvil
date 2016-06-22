/*
************************************
* Copyright (C) 2016 ByteForge
* Math.cpp
************************************
*/

#include "Math.hpp"

using namespace anvil;

const glm::vec3  Math::ComputeNormal(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
	return glm::normalize(glm::cross(c - b, a - b));
}

