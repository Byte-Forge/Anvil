#include "Math.hpp"

using namespace hpse;

glm::vec3  Math::ComputeNormal(float& a, float& b, float& c)
{
	glm::vec3 va = { 0.0, a, 0.0 };
	glm::vec3 vb = { 0.0, b, 1.0 };
	glm::vec3 vc = { 1.0, c, 1.0 };
	return ComputeNormal(va, vb, vc);
}

glm::vec3  Math::ComputeNormal(glm::vec3& a, glm::vec3& b, glm::vec3& c)
{
	return glm::normalize(glm::cross(c - b, a - b));
}

