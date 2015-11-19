#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <map>
#include "../Core/IResource.hpp"

namespace hpse
{
	//#######################################################################################
	//# basic structs
	//#######################################################################################

	struct RGBA
	{
		glm::uint8 r, g, b, a;
	};

	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	// chunk 257
	struct HierarchyHeader
	{
		string name;
		glm::uint32 pivotCount;
		glm::f32vec3 centerPos;
	};

	// chunk 258
	struct HierarchyPivot
	{
		string name;
		glm::uint16 parentID;
		glm::uint8 isBone;
		glm::f32vec3 position;
		glm::f32vec4 rotation; //use quat here instead??
	};

	// chunk 256
	class Hierarchy : public IResource
	{
	public:
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
		glm::int32 numFrames;
		glm::int32 frameRate;
	};

	struct TimeCodedAnimationKey
	{
		glm::uint16 frame;
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
		glm::uint16 vectorLen;
		glm::int8 type;
		glm::uint16 pivot;
		vector<TimeCodedAnimationKey> timeCodedKeys;
	};

	// chunk 512
	class Animation 
	{
	public:
		AnimationHeader header;
		vector<TimeCodedAnimationChannel> channels;
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
		glm::uint16 boneIdx;
		glm::uint16 boneInf;
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
		glm::uint8 type; //0 standard, 1 normal, 2 displacement
		glm::float32 value; // factor for normal, displacement etc
		//TextureAnimation animations[1];
	};

	//#######################################################################################
	//# material
	//#######################################################################################	

	// chunk 30
	struct MeshMaterial
	{
		RGBA diffuse;
		glm::float32 diffuse_intensity;
		RGBA specular;
		glm::float32 specular_intensity;
		glm::float32 emit;
		glm::float32 alpha;
		vector<Texture> textures;
	};

	//#######################################################################################
	//# mesh
	//#######################################################################################	

	// chunk 2
	struct MeshHeader
	{
		glm::uint8 type;
		// 0->normal mesh
		// 1->normal mesh - two sided
		// 2->normal mesh - camera oriented
		// 128->skin
		// 129->skin - two sided

		string meshName;
		glm::uint16 parentPivot;
		glm::uint32 faceCount;
		glm::uint32 vertCount;
	};

	// chunk 1
	struct Mesh
	{
		MeshHeader header;
		vector<glm::f32vec3> vertices;
		vector<glm::f32vec3> normals;
		vector<glm::i32vec3> faces;
		vector<glm::f32vec2> uvCoords;
		vector<MeshVertexInfluences> vertInfs;
		vector<MeshMaterial> materials;
	};

	//#######################################################################################
	//# model
	//#######################################################################################

	// chunk 0
	class W4DModel : public IResource
	{
	public:
		string name;
		string hieraName; // is the name of the model by default
		std::map<std::string, Mesh> meshes;
		BoundingVolume volume;
	};
}
