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

bool Collision::Contains2D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size)
{
	return (vertex.x >= center.x - size.x
		&& vertex.x <= center.x + size.x
		&& vertex.z >= center.z - size.z
		&& vertex.z <= center.z + size.z);
}

bool Collision::Contains3D(const glm::vec3& vertex, const glm::vec3& center, const glm::vec3& size)
{
	return (vertex.x >= center.x - size.x
		&& vertex.x <= center.x + size.x
		&& vertex.y >= center.y - size.y
		&& vertex.y <= center.y + size.y
		&& vertex.z >= center.z - size.z
		&& vertex.z <= center.z + size.z);
}

bool Collision::CubeInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, const glm::vec3& size)
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

int Collision::SphereInFrustum(const std::array<std::array<float, 4>, 6>& frustum, const glm::vec3& center, float radius)
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

int Collision::Ray_Tri_Intersect(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3, const glm::vec3 & o, const glm::vec3 & d, glm::vec3 & point)
{
	glm::vec3 e1, e2;  //Edge1, Edge2
	glm::vec3 P, Q, T;
	float det, inv_det, u, v;
	float t;

	//Find vectors for two edges sharing v1
	e1 = v2 - v1;
	e2 = v3 - v1;
	//Begin calculating determinant - also used to calculate u parameter
	P = glm::cross(d, e2);
	//if determinant is near zero, ray lies in plane of triangle
	det = glm::dot(e1, P);
	//NOT CULLING
	if (det > -EPSILON && det < EPSILON) return 0;
	inv_det = 1.f / det;

	//calculate distance from v1 to ray origin
	T = o - v1;

	//Calculate u parameter and test bound
	u = glm::dot(T, P) * inv_det;
	//The intersection lies outside of the triangle
	if (u < 0.f || u > 1.f) return 0;

	//Prepare to test v parameter
	Q = glm::cross(T, e1);

	//Calculate v parameter and test bound
	v = glm::dot(d, Q) * inv_det;
	//The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f) return 0;

	t = glm::dot(e2, Q) * inv_det;

	//the point of the collision is t * d
	if (t > EPSILON) { //ray intersection
		point = t * d;
		return 1;
	}

	// No hit, no win
	return 0;
}

//
bool TestRayOBBIntersection(
	glm::vec3 ray_origin,        // Ray origin, in world space
	glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
	glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
	glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
	glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
	float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
	) {

	// Intersection method from Real-Time Rendering and Essential Mathematics for Games

	float tMin = 0.0f;
	float tMax = 100000.0f;

	glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

	glm::vec3 delta = OBBposition_worldspace - ray_origin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
		float e = glm::dot(xaxis, delta);
		float f = glm::dot(ray_direction, xaxis);

		if (fabs(f) > 0.001f) { // Standard case

			float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
			float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
											 // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

											 // We want t1 to represent the nearest intersection, 
											 // so if it's not the case, invert t1 and t2
			if (t1>t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
				return false;

		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
		float e = glm::dot(yaxis, delta);
		float f = glm::dot(ray_direction, yaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.y) / f;
			float t2 = (e + aabb_max.y) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
		float e = glm::dot(zaxis, delta);
		float f = glm::dot(ray_direction, zaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + aabb_min.z) / f;
			float t2 = (e + aabb_max.z) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
				return false;
		}
	}

	intersection_distance = tMin;
	return true;
}

