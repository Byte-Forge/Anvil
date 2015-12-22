#pragma once
#include <glm/glm.hpp>

namespace hpse
{
	class Math
	{
	public:
		static glm::vec3  Math::computeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c);
	};
}