#include "W4DLoader.hpp"

#include <fstream>
#include <iostream>
#include <memory> 
#include <glm/glm.hpp>
#include "Util.hpp"        
#include "../Types/W4D.hpp"
#include "../Core/ResourceHandler.hpp"
#include <stdint.h>

using namespace std;
using namespace hpse;

//#######################################################################################
//# hierarchy
//#######################################################################################

HierarchyHeader loadHierarchyHeader(ifstream& file)
{
	HierarchyHeader header;
	header.name = readString(file);
	header.pivotCount = read<std::uint32_t>(file);
	header.centerPos = read<glm::f32vec3>(file);
	return header;
}

HierarchyPivot loadHierarchyPivot(ifstream& file)
{
	HierarchyPivot pivot;
	pivot.name =  readString(file);
	pivot.parentID = read<std::uint16_t>(file);
	pivot.isBone = read<std::uint8_t>(file);
	pivot.position = read<glm::f32vec3>(file);
	pivot.rotation =  read<glm::f32vec4>(file);
	return pivot;
}

void loadHierarchy(ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<Hierarchy> hierarchy;
	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 257:
			hierarchy->header = loadHierarchyHeader(file);
			break;
		case 258:
			hierarchy->pivots.push_back(loadHierarchyPivot(file));
			break;
		default:
			cout << "unknown chunktype in hierarchy chunk: " << chunkType << endl;
			file.seekg(0, chunkEnd);
		}
	}
	//ResourceHandler::instance()->AddResource(hierarchy->header->name, shared_ptr<IResource>(&hierarchy));
}

//#######################################################################################
//# model
//#######################################################################################

Texture loadTexture(ifstream& file)
{
	Texture texture;
	texture.name = readString(file);
	texture.type = read<std::uint8_t>(file);
	texture.value = read<glm::float32>(file);
	return texture;
}

MeshMaterial loadMeshMaterial(ifstream& file, std::uint32_t chunkEnd)
{
	MeshMaterial material;
	material.diffuse = read<RGBA>(file);
	material.diffuse_intensity = read<glm::float32>(file);
	material.specular = read<RGBA>(file);
	material.specular_intensity = read<glm::float32>(file);
	material.emit = read<glm::float32>(file);
	material.alpha = read<glm::float32>(file);

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 31:
			material.textures.push_back(loadTexture(file));
			break;
		default:
			cout << "unknown chunktype in mesh material chunk: " << chunkType << endl;
			file.seekg(0, chunkEnd);
		}
	}
	return material;
}

MeshHeader loadMeshHeader(ifstream& file)
{
	MeshHeader header;
	header.type = read<std::uint8_t>(file);
	header.meshName = readString(file);
	header.parentPivot = read<std::uint16_t>(file);
	header.faceCount = read<std::uint32_t>(file);
	header.vertCount = read<std::uint32_t>(file);
	return header;
}

Mesh loadMesh(ifstream& file, std::uint32_t chunkEnd)
{
	Mesh mesh;
	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 2:
			mesh.header = loadMeshHeader(file);
			break;
		case 3:
			while (file.tellg() < chunkEnd)
				mesh.vertices.push_back(read<glm::f32vec3>(file));
			break;
		case 4:
			while (file.tellg() < chunkEnd)
				mesh.normals.push_back(read<glm::f32vec3>(file));
			break;
		case 5:
			while (file.tellg() < chunkEnd)
				mesh.faces.push_back(read<glm::i32vec3>(file));
			break;
		case 6:
			while (file.tellg() < chunkEnd)
				mesh.uvCoords.push_back(read<glm::f32vec2>(file));
			break;
		case 7:
			while (file.tellg() < chunkEnd)
				mesh.vertInfs.push_back(read<MeshVertexInfluences>(file));
			break;
		case 30:
			mesh.materials.push_back(loadMeshMaterial(file, chunkEnd));
			break;
		default:
			cout << "unknown chunktype in mesh chunk: " << chunkType << endl;
			file.seekg(0, chunkEnd);	
		}
	}
	return mesh;
}

void loadModel(ifstream& file, std::uint32_t chunkEnd)
{
	W4DModel model;
	model.name = readString(file);
	model.hieraName = readString(file);

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		Mesh m;
		switch (chunkType)
		{
		case 1:
			m = loadMesh(file, chunkEnd);
			model.meshes.insert({m.header.meshName, m});
			break;
		case 1024:
			model.volume = read<Box>(file);
			break;
		case 1025:
			model.volume = read<Sphere>(file);
			break;
		default:
			cout << "unknown chunktype in model chunk: " << chunkType << endl;
			file.seekg(0, chunkEnd);
		}
	}
	std::shared_ptr<IResource> p (&model);
	ResourceHandler::instance()->AddResource(model.name, p);
}

void W4DLoader::Load(const std::string& name)
{
	string path = "w4d\\";
	string ext = ".w4d";

	ifstream file(path + name + ext, ios::binary);
	long size = getFStreamSize(file);

	while (file.tellg() < size)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 0:
			cout << "loading model: " << name << endl;
			loadModel(file, chunkEnd);
			break;
		case 256:
			cout << "loading hierarchy: " << name << endl;
			loadHierarchy(file, chunkEnd);
			break;

		default:
			cout << "unknown chunktype in file: " << chunkType << endl;
			file.seekg(0, chunkEnd);
		}
	}
}
