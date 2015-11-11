#pragma once
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

namespace hpse
{
	//#######################################################################################
	//# basic structs
	//#######################################################################################

	struct RGBA
	{
		uint8 r, g, b, a;
	};

	//#######################################################################################
	//# model
	//#######################################################################################

	// chunk 0
	struct Model
	{
		string name;
		string hieraName; // is the name of the model by default
		BoundingVolume volume;
		Mesh meshes[1];
	};

	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	// chunk 257
	struct HierarchyHeader
	{
		string name;
		int32 pivotCount;
		f32vec3 centerPos;
	};

	// chunk 258
	struct HierarchyPivot
	{
		string name;
		uint16 parentID;
		uint8 isBone;
		f32vec3 position;
		f32vec4 rotation; //use quat here instead??
	};

	// chunk 256
	struct Hierarchy
	{
		HierarchyHeader header;
		HierarchyPivot pivots[1];
	};

	//#######################################################################################
	//# animation
	//#######################################################################################

	// chunk 513
	struct AnimationHeader
	{
		string name;
		string hieraName;
		int32 numFrames;
		int32 frameRate;
	};

	struct TimeCodedAnimationKey
	{
		uint16 frame;
	};

	struct TimeCodedAnimationFloatKey : TimeCodedAnimationKey
	{
		float32 value;
	};

	struct TimeCodedAnimationQuatKey : TimeCodedAnimationKey
	{
		f32vec4 value; // use quat here instead ?
	};

	// chunk 514
	struct TimeCodedAnimationChannel
	{
		uint16 vectorLen;
		int8 type;
		uint16 pivot;
		TimeCodedAnimationKey timeCodedKeys[1];
	};

	// chunk 512
	struct Animation
	{
		AnimationHeader header;
		TimeCodedAnimationChannel channels[1];
	};

	//#######################################################################################
	//# bounding volumes
	//#######################################################################################

	struct BoundingVolume
	{
		f32vec3 center;
	};

	// chunk 1024
	struct Box : BoundingVolume
	{
		f32vec3 extend;
	};

	// chunk 1025
	struct Shpere : BoundingVolume
	{
		float32 radius;
	};

	//#######################################################################################
	//# vertexInfluences
	//#######################################################################################

	// chunk 7
	struct MeshVertexInfluences
	{
		uint16 boneIdx;
		uint16 boneInf;
	};

	//#######################################################################################
	//  texture animation
	//#######################################################################################		

	// chunk 32
	//struct TextureAnimation 
	//{
	//not sure what values we need here
	//};

	//#######################################################################################
	//# texture
	//#######################################################################################	

	// chunk 31
	struct Texture
	{
		string name;
		uint8 type; //0 standard, 1 normal, 2 displacement
		float32 value; // factor for normal, displacement etc
					   //TextureAnimation animations[1];
	};

	//#######################################################################################
	//# material
	//#######################################################################################	

	// chunk 30
	struct MeshMaterial
	{
		RGBA diffuse;
		float32 diffuse_intensity;
		RGBA specular;
		float32 specular_intensity;
		float32 emit;
		float32 alpha;
		Texture textures[1];
	};

	//#######################################################################################
	//# mesh
	//#######################################################################################	

	// chunk 2
	struct MeshHeader
	{
		uint8 type;
		// 0->normal mesh
		// 1->normal mesh - two sided
		// 2->normal mesh - camera oriented
		// 128->skin
		// 129->skin - two sided

		string meshName;
		uint16 parentPivot;
		uint32 faceCount;
		uint32 vertCount;
	};

	// chunk 1
	struct Mesh
	{
		MeshHeader header;
		f32vec3 verts[1];
		f32vec3 normals[1];
		i32vec3 faces[1];
		f32vec2 uvCoords[1];
		MeshVertexInfluences vertInfs[1];
		MeshMaterial materials[1];
	};
}
