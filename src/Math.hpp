#pragma once
#include <glm/glm.hpp>

namespace hpse
{
	class Math
	{
	public:
		static glm::vec3  ComputeNormal(float& a, float& b, float& c);
		static glm::vec3  ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c);
	};
}