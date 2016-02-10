/*
************************************
* Copyright (C) 2016 ByteForge
* Math.hpp
************************************
*/

#pragma once
#include <glm/glm.hpp>

namespace anvil
{
	class Math
	{
	public:
		static glm::vec3  ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c);
	};
}