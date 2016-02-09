#include "BF3DLoader.hpp"

#include <fstream>
#include <iostream>
#include <memory> 
#include <glm/glm.hpp>
#include "Util.hpp"        
#include "../Core.hpp"
#include "../Types/BF3D.hpp"
#include "../Core/ResourceHandler.hpp"
#include <stdint.h>

using namespace hpse;

//#######################################################################################
//# hierarchy
//#######################################################################################

HierarchyHeader loadHierarchyHeader(std::ifstream& file)
{
	HierarchyHeader header;
	header.name = readString(file);
	header.pivotCount = read<std::uint32_t>(file);
	header.centerPos = read<glm::f32vec3>(file);
	return header;
}

HierarchyPivot loadHierarchyPivot(std::ifstream& file)
{
	HierarchyPivot pivot;
	pivot.name =  readString(file);
	pivot.parentID = read<std::uint16_t>(file);
	pivot.isBone = read<std::uint8_t>(file);
	pivot.position = read<glm::f32vec3>(file);
	pivot.rotation =  read<glm::f32vec4>(file);
	return pivot;
}

void loadHierarchy(std::string name, std::ifstream& file, std::uint32_t chunkEnd)
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
			hierarchy = std::make_shared<Hierarchy>();
			hierarchy->header = loadHierarchyHeader(file);
			break;
		case 258:
			hierarchy->pivots.push_back(loadHierarchyPivot(file));
			break;
		default:
			std::cout << "unknown chunktype in hierarchy chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	Core::GetCore()->GetResources()->AddResource(name, hierarchy);
}

//#######################################################################################
//# model
//#######################################################################################

MeshHeader loadMeshHeader(std::ifstream& file)
{
	MeshHeader header;
	header.type = read<std::uint8_t>(file);
	header.meshName = readString(file);
	header.materialID = read<std::uint16_t>(file);
	header.parentPivot = read<std::uint16_t>(file);
	header.faceCount = read<std::uint32_t>(file);
	header.vertCount = read<std::uint32_t>(file);
	return header;
}

Mesh loadMesh(std::ifstream& file, std::uint32_t chunkEnd)
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
			//read the at once?
			while (file.tellg() < chunkEnd)
				mesh.vertices.push_back(read<glm::f32vec3>(file));
			break;
		case 4:
			//read the at once?
			while (file.tellg() < chunkEnd)
				mesh.normals.push_back(read<glm::f32vec3>(file));
			break;
		case 5:
			//read the at once?
			while (file.tellg() < chunkEnd)
				mesh.faces.push_back(read<glm::i32vec3>(file));
			break;
		case 6:
			//read the at once?
			while (file.tellg() < chunkEnd)
				mesh.uvCoords.push_back(read<glm::f32vec2>(file));
			break;
		case 7:
			//read the at once?
			while (file.tellg() < chunkEnd)
				mesh.vertInfs.push_back(read<MeshVertexInfluences>(file));
			break;
		default:
			std::cout << "unknown chunktype in mesh chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	return mesh;
}

void loadModel(std::string name, std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<BF3DModel> model =  std::make_shared<BF3DModel>();
	model->hieraName = readString(file);

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 1:
			model->meshes.push_back(loadMesh(file, chunkEnd));
			break;
		case 1024:
			model->volume = read<Box>(file);
			break;
		case 1025:
			model->volume = read<Sphere>(file);
			break;
		default:
			std::cout << "unknown chunktype in model chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	Core::GetCore()->GetResources()->AddResource(name, model);
}

void BF3DLoader::Load(const std::string& name, const std::string& path)
{
	std::ifstream file(path, std::ios::binary);
	long size = getFStreamSize(file);

	while (file.tellg() < size)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = (long)file.tellg() + chunkSize;

		switch (chunkType)
		{
		case 0:
			loadModel(name, file, chunkEnd);
			break;
		case 256:
			loadHierarchy(name, file, chunkEnd);
			break;

		default:
			std::cout << "unknown chunktype in file: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
}
