/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.cpp
************************************
*/

#include "BF3DLoader.hpp"
#include <fstream>
#include <iostream>
#include <memory> 
#include <glm/glm.hpp>
#include "Util.hpp"        
#include "../Core.hpp"
#include "../Types/BF3D.hpp"
#include "../Graphics/IMesh.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/GL/MeshGL.hpp"
#include "../Graphics/GL/ModelGL.hpp"
#include "../Core/ResourceHandler.hpp"
#include <stdint.h>

using namespace anvil;

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

void BF3DLoader::LoadHierarchy(std::string name, std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<Hierarchy> hierarchy;
	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		size_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;

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

void BF3DLoader::LoadMesh(std::ifstream& file, std::uint32_t chunkEnd)
{
	/*
	auto mesh = *Core::GetCore()->GetGraphics()->GetMesh();

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;
		std::cout << chunkType << std::endl;
		switch (chunkType)
		{
		case 2:
			mesh.m_type = read<std::uint8_t>(file);
			mesh.m_meshName = readString(file);
			mesh.m_materialID = read<std::uint16_t>(file);
			mesh.m_parentPivot = read<std::uint16_t>(file);
			mesh.m_faceCount = read<std::uint32_t>(file);
			mesh.m_vertCount = read<std::uint32_t>(file);
			break;
		case 3:
			mesh.m_vertices = readVector<glm::f32vec3>(file, chunkSize);
			std::cout << mesh.m_vertices.size() << std::endl;
			break;
		case 4:
			mesh.m_normals = readVector<glm::f32vec3>(file, chunkSize);
			break;
		case 5:
			mesh.m_faces = readVector<glm::i32vec3>(file, chunkSize);
			break;
		case 6:
			mesh.m_uvCoords = readVector<glm::f32vec2>(file, chunkSize);
			break;
		case 7:
			mesh.m_vertInfs = readVector<IMesh::MeshVertexInfluences>(file, chunkSize);
			break;
		default:
			std::cout << "unknown chunktype in mesh chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	mesh.Update();
	return &mesh;
	*/
}

void BF3DLoader::LoadModel(std::string name, std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<IModel> model = Core::GetCore()->GetGraphics()->GetModel();
	model->m_hierarchyName = readString(file);

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;
		switch (chunkType)
		{
		case 1:
			//model->m_meshes.push_back(LoadMesh(file, chunkEnd));
			LoadMesh(file, chunkEnd);
			break;
		case 1024:
			model->m_volume = read<IModel::Box>(file);
			break;
		case 1025:
			model->m_volume = read<IModel::Sphere>(file);
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
		std::uint32_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		switch (chunkType)
		{
		case 0:
			LoadModel(name, file, chunkEnd);
			break;
		case 256:
			LoadHierarchy(name, file, chunkEnd);
			break;

		default:
			std::cout << "unknown chunktype in file: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
}
