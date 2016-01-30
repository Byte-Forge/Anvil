#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Core/IResource.hpp"
#include <stdint.h>

namespace hpse
{
	//#######################################################################################
	//# basic structs
	//#######################################################################################

	struct RGBA
	{
		std::uint8_t r, g, b, a;
	};

	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	// chunk 257
	struct HierarchyHeader
	{
		std::string name;
		std::uint32_t pivotCount;
		glm::f32vec3 centerPos;
	};

	// chunk 258
	struct HierarchyPivot
	{
		std::string name;
		std::uint16_t parentID;
		std::uint8_t isBone;
		glm::f32vec3 position;
		glm::f32vec4 rotation; //use quat here instead??
	};

	// chunk 256
	class Hierarchy : public IResource
	{
	public:
		HierarchyHeader header;
		std::vector<HierarchyPivot> pivots;
	};

	//#######################################################################################
	//# animation
	//#######################################################################################

	// chunk 513
	struct AnimationHeader
	{
		std::string name;
		std::string hieraName;
		std::int32_t numFrames;
		std::int32_t frameRate;
	};

	struct TimeCodedAnimationKey
	{
		std::uint16_t frame;
	};

	struct TimeCodedAnimationFloatKey : TimeCodedAnimationKey
	{
		glm::float32 value;
	};

	struct TimeCodedAnimationQuatKey : TimeCodedAnimationKey
	{
		glm::f32vec4 value; // use quat here instead ?
	};

	// chunk 514
	struct TimeCodedAnimationChannel
	{
		std::uint16_t vectorLen;
		std::int8_t type;
		std::uint16_t pivot;
		std::vector<TimeCodedAnimationKey> timeCodedKeys;
	};

	// chunk 512
	class Animation 
	{
	public:
		AnimationHeader header;
		std::vector<TimeCodedAnimationChannel> channels;
	};

	//#######################################################################################
	//# bounding volumes
	//#######################################################################################

	struct BoundingVolume
	{
		glm::f32vec3 center;
	};

	// chunk 1024
	struct Box : BoundingVolume
	{
		glm::f32vec3 extend;
	};

	// chunk 1025
	struct Sphere : BoundingVolume
	{
		glm::float32 radius;
	};

	//#######################################################################################
	//# vertexInfluences
	//#######################################################################################

	// chunk 7
	struct MeshVertexInfluences
	{
		std::uint16_t boneIdx;
		std::uint16_t boneInf;
	};

	//#######################################################################################
	//# mesh
	//#######################################################################################	

	// chunk 2
	struct MeshHeader
	{
		std::uint8_t type;
		// 0->normal mesh
		// 1->normal mesh - two sided
		// 2->normal mesh - camera oriented
		// 128->skin
		// 129->skin - two sided

		std::string meshName;
		std::uint16_t materialID;
		std::uint16_t parentPivot;
		glm::uint32 faceCount;
		glm::uint32 vertCount;
	};

	// chunk 1
	struct Mesh
	{
		MeshHeader header;
		std::vector<glm::f32vec3> vertices;
		std::vector<glm::f32vec3> normals;
		std::vector<glm::f32vec2> uvCoords;
		std::vector<glm::i32vec3> faces;
		std::vector<MeshVertexInfluences> vertInfs;
	};

	//#######################################################################################
	//# model
	//#######################################################################################

	// chunk 0
	class W4DModel : public IResource
	{
	public:
		std::string hieraName; // is the name of the model by default
		std::vector<Mesh> meshes;
		BoundingVolume volume;
	};
}
