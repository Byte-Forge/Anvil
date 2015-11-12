#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>

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
	struct W4DModel : IResource
	{
		string name;
		string hieraName; // is the name of the model by default
		std::map<std::string, Mesh> meshes;
		BoundingVolume volume;
	};

	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	// chunk 257
	struct HierarchyHeader
	{
		string name;
		uint32 pivotCount;
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
	struct Hierarchy : IResource
	{
		HierarchyHeader header;
		vector<HierarchyPivot> pivots;
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
		vector<TimeCodedAnimationKey> timeCodedKeys;
	};

	// chunk 512
	struct Animation : IResource
	{
		AnimationHeader header;
		vector<TimeCodedAnimationChannel> channels;
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
	struct Sphere : BoundingVolume
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
		vector<Texture> textures;
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
		vector<f32vec3> vertices;
		vector<f32vec3> normals;
		vector<i32vec3> faces;
		vector<f32vec2> uvCoords;
		vector<MeshVertexInfluences> vertInfs;
		vector<MeshMaterial> materials;
	};
}
