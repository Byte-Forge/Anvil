#include "Math.hpp"

using namespace hpse;

glm::vec3  Math::ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c)
{
	return glm::normalize(glm::cross(c - b, a - b));
}

