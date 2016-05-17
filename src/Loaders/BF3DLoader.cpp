/*
************************************
* Copyright (C) 2016 ByteForge
* BF3DLoader.cpp
************************************
*/

#include "BF3DLoader.hpp"
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include "../Util.hpp"        
#include "../Core.hpp"
#include "../Graphics.hpp"
#include "../Graphics/Hierarchy.hpp"
#include "../Graphics/Animation.hpp"
#include "../Graphics/IModel.hpp"
#include "../Graphics/GL/MeshGL.hpp"
#include "../Graphics/GL/ModelGL.hpp"
#include "../Core/ResourceHandler.hpp"

using namespace anvil;

//#######################################################################################
//# hierarchy
//#######################################################################################

void BF3DLoader::LoadHierarchy(const std::string &name, std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<Hierarchy> hierarchy;
	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t subChunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		switch (chunkType)
		{
		case 257:
			hierarchy = std::make_shared<Hierarchy>();
			hierarchy->SetName(readString(file));
			hierarchy->SetPivotCount(read<std::uint32_t>(file));
			hierarchy->SetCenterPos(read<glm::f32vec3>(file));
			break;
		case 258:
			while (file.tellg() < subChunkEnd)
			{
				readString(file); //the name of the pivot (not used in the engine)
				hierarchy->AddParentID(read<std::int32_t>(file)); //parent pivot of the bone
				read<std::uint8_t>(file); //if the pivot is a bone (not used in the engine)
				hierarchy->AddPivot(read<glm::f32mat4x4>(file));
			}
			break;
		default:
			std::cout << "unknown chunktype in hierarchy chunk: " << chunkType << std::endl;
			file.seekg(subChunkEnd, std::ios::beg);
		}
	}
	Core::GetCore()->GetResources()->AddResource(name, hierarchy);
}

//#######################################################################################
//# animation
//#######################################################################################

void BF3DLoader::LoadAnimation(const std::string &name, std::ifstream &file, std::uint32_t chunkEnd)
{
	std::shared_ptr<Animation> animation;
	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t subChunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		std::int32_t pivot;
		std::int32_t extrapolation;
		std::int32_t type;

		std::map<int, glm::f32> frames;
		std::unordered_map<int, std::map<int, glm::f32>> channels;

		switch (chunkType)
		{
		case 513:
			animation = std::make_shared<Animation>();
			animation->SetName(readString(file));
			animation->SetHierarchyName(readString(file));
			animation->SetFrameRate(read<std::int32_t>(file));
			animation->SetNumFrames(read<std::int32_t>(file));
			break;
		case 514:
			pivot = read<std::int32_t>(file);
			extrapolation = read<std::int32_t>(file);
			type = read<std::int32_t>(file);
			frames.clear();
			channels.clear();

			while (file.tellg() < subChunkEnd)
			{
				std::int32_t frame = read<std::int32_t>(file);
				glm::f32 value = read<glm::f32>(file);
				frames.insert({ frame, value });
			}
			channels.insert({ type, frames });
			animation->AddChannel(pivot, channels);
			break;
		default:
			std::cout << "unknown chunktype in animation chunk: " << chunkType << std::endl;
			file.seekg(subChunkEnd, std::ios::beg);
		}
	}
	Core::GetCore()->GetResources()->AddResource(name, animation);
}

//#######################################################################################
//# model
//#######################################################################################

std::shared_ptr<IMesh> BF3DLoader::LoadMesh(std::ifstream& file, std::uint32_t chunkEnd)
{
	std::shared_ptr<IMesh> mesh = Core::GetCore()->GetGraphics()->GetMesh();

	while (file.tellg() < chunkEnd)
	{
		std::uint32_t chunkType = read<std::int32_t>(file);
		std::uint32_t chunkSize = read<std::int32_t>(file);
		std::uint32_t subChunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		switch (chunkType)
		{
		case 2:
			mesh->SetType(read<std::uint8_t>(file));
			mesh->SetName(readString(file));
			mesh->SetMaterialID(read<std::int32_t>(file));
			mesh->SetParentPivot(read<std::int32_t>(file));
			mesh->SetFaceCount(read<std::int32_t>(file));
			mesh->SetVerticesCount(read<std::int32_t>(file));
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
			mesh->SetVertInfs(readVector<glm::i32vec2>(file, chunkSize));
			break;
		default:
			std::cout << "unknown chunktype in mesh chunk: " << chunkType << std::endl;
			file.seekg(subChunkEnd, std::ios::beg);
		}
	}
	mesh->Init();
	return mesh;
}

void BF3DLoader::LoadModel(const std::string &name, std::ifstream& file, std::uint32_t chunkEnd, const std::string &skl_path)
{
	std::shared_ptr<IModel> model = Core::GetCore()->GetGraphics()->GetModel();
	std::string hierarchyName = readString(file);
	if (hierarchyName != "")
		model->SetHierarchy(Core::GetCore()->GetResources()->GetHierarchy(skl_path + hierarchyName + ".bf3d"));
	else
		model->SetHierarchy(nullptr);

	while (file.tellg() < chunkEnd)
	{
		std::int32_t chunkType = read<std::int32_t>(file);
		std::int32_t chunkSize = read<std::int32_t>(file);
		std::int32_t subChunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		std::shared_ptr<IMesh> mesh;
		switch (chunkType)
		{
		case 1:
			mesh = LoadMesh(file, subChunkEnd);
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

void BF3DLoader::Load(const std::string& name, const std::string& path, const std::string& skl_path)
{
	std::ifstream file(path, std::ios::binary);
	long size = getFStreamSize(file);

	while (file.tellg() < size)
	{
		std::uint32_t chunkType = read<std::uint32_t>(file);
		std::uint32_t chunkSize = read<std::uint32_t>(file);
		std::uint32_t subChunkEnd = static_cast<long>(file.tellg()) + chunkSize;

		switch (chunkType)
		{
		case 0:
			LoadModel(name, file, subChunkEnd, skl_path);
			break;
		case 256:
			LoadHierarchy(name, file, subChunkEnd);
			break;
		case 512:
			LoadAnimation(name, file, subChunkEnd);
			break;

		default:
			std::cout << "unknown chunktype in file: " << chunkType << std::endl;
			file.seekg(subChunkEnd, std::ios::beg);
		}
	}
}

