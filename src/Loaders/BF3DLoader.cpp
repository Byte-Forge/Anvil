/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.cpp
************************************
*/

#include "BF3DLoader.hpp"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include "../Util.hpp"        
#include "../Core.hpp"
#include "../Types/BF3D.hpp"
#include "../Graphics.hpp"
//#include "../Graphics/IModel.hpp"
//#include "../Graphics/GL/MeshGL.hpp"
//#include "../Graphics/GL/ModelGL.hpp"
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
/*
std::shared_ptr<IMesh> BF3DLoader::LoadMesh(std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<IMesh> mesh = Core::GetCore()->GetGraphics()->GetMesh();

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		switch (chunkType)
		{
		case 2:
			mesh->SetType(read<std::uint8_t>(file));
			mesh->SetName(readString(file));
			mesh->SetMaterialID(read<std::uint16_t>(file));
			mesh->SetParentPivot(read<std::uint16_t>(file));
			mesh->SetFaceCount(read<std::uint32_t>(file));
			mesh->SetVerticesCount(read<std::uint32_t>(file));
			break;
		case 3:
			mesh->SetVertices(readVector<glm::f32vec3>(file, chunkSize));
			break;
		case 4:
			mesh->SetNormals(readVector<glm::f32vec3>(file, chunkSize));
			break;
		case 5:
			mesh->SetFaces(readVector<glm::i32vec3>(file, chunkSize));
			break;
		case 6:
			mesh->SetUVCoords(readVector<glm::f32vec2>(file, chunkSize));
			break;
		case 7:
			mesh->SetVertInfs(readVector<IMesh::MeshVertexInfluences>(file, chunkSize));
			break;
		default:
			std::cout << "unknown chunktype in mesh chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	mesh->Init();
	return mesh;
}
*/

/*
void BF3DLoader::LoadModel(std::string name, std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<IModel> model = Core::GetCore()->GetGraphics()->GetModel();
	std::cout << name << std::endl;
	std::string hierarchyName = readString(file);
	if (hierarchyName != "")
		model->SetHierarchy(Core::GetCore()->GetResources()->GetHierarchy("units/mucavtroll_skl.bf3d"));
	else
		model->SetHierarchy(nullptr);

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t chunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		std::shared_ptr<IMesh> mesh;
		switch (chunkType)
		{
		case 1:
			mesh = LoadMesh(file, chunkEnd);
			model->AddMesh(mesh->GetName(), mesh);
			break;
		case 1024:
			model->SetBoundingVolume(read<IModel::Box>(file));
			break;
		case 1025:
			model->SetBoundingVolume(read<IModel::Sphere>(file));
			break;
		default:
			std::cout << "unknown chunktype in model chunk: " << chunkType << std::endl;
			file.seekg(chunkEnd, std::ios::beg);
		}
	}
	Core::GetCore()->GetResources()->AddResource(name, model);
	Core::GetCore()->GetGraphics()->GetRenderer()->RegisterRenderable(model);
}
*/

/*
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
*/
