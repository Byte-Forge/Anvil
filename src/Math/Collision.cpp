/*
************************************
* Copyright (C) 2016 ByteForge
* Collision.cpp
************************************
*/

#include "Collision.hpp"
#include "../Core.hpp"
#include <iostream>

using namespace anvil;


bool Collision::CubeInFrustum(const std::array<glm::vec4, 6>& frustum, const glm::vec3& center, const glm::vec3& size)
{
	for (int p = 0; p < 6; p++)
	{
		if (frustum[p][0] * (center.x - size.x) + frustum[p][1] * (center.y - size.y) + frustum[p][2] * (center.z - size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x - size.x) + frustum[p][1] * (center.y - size.y) + frustum[p][2] * (center.z + size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x - size.x) + frustum[p][1] * (center.y + size.y) + frustum[p][2] * (center.z - size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x - size.x) + frustum[p][1] * (center.y + size.y) + frustum[p][2] * (center.z + size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x + size.x) + frustum[p][1] * (center.y - size.y) + frustum[p][2] * (center.z - size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x + size.x) + frustum[p][1] * (center.y - size.y) + frustum[p][2] * (center.z + size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x + size.x) + frustum[p][1] * (center.y + size.y) + frustum[p][2] * (center.z - size.z) + frustum[p][3] > 0)
			continue;
		if (frustum[p][0] * (center.x + size.x) + frustum[p][1] * (center.y + size.y) + frustum[p][2] * (center.z + size.z) + frustum[p][3] > 0)
			continue;
		return false;
	}
	return true;
}

int Collision::SphereInFrustum(const std::array<glm::vec4, 6>& frustum, const glm::vec3& center, float radius)
{
	int p;
	int c = 0;
	float d;

	for (p = 0; p < 6; p++)
	{
		d = frustum[p][0] * center.x + frustum[p][1] * center.y + frustum[p][2] * center.z + frustum[p][3];
		if (d <= -radius)
			return 0;
		if (d > radius)
			c++;
	}
	return (c == 6) ? 2 : 1;
}
