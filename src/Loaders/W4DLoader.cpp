#include "W4DLoader.hpp"

#include <fstream>
#include <iostream>
#include "Util.hpp"
#include "../Graphics/GL/Model.hpp"
#include "../Types/W4D.hpp"

using namespace std;
using namespace hpse;

namespace hpse
{
	//#######################################################################################
	//# hierarchy
	//#######################################################################################

	HierarchyHeader loadHierarchyHeader(ifstream& file)
	{
		HierarchyHeader header;
		header.name = readString(file);
		header.pivotCount = read<uint32>(file);
		header.centerPos = read<f32vec3>(file);
		return header;
	}

	HierarchyPivot loadHierarchyPivot(ifstream& file)
	{
		HierarchyPivot pivot;
		pivot.name =  readString(file);
		pivot.parentID = read<uint16>(file);
		pivot.isBone = read<uint8>(file);
		pivot.position = read<f32vec3>(file);
		pivot.rotation =  read<f32vec4>(file);
		return pivot;
	}

	Hierarchy loadHierarchy(ifstream& file, uint32 chunkEnd)
	{
		Hierarchy hierarchy;
		while (file.tellg() < chunkEnd)
		{
			uint32 chunkType = read<uint32>(file);
			uint32 chunkSize = GetChunkSize(read<uint32>(file));
			uint32 chunkEnd = (long)file.tellg() + chunkSize;

			switch (chunkType)
			{
			case 257:
				hierarchy.header = loadHierarchyHeader(file);
				break;
			case 258:
				hierarchy.pivots.push_back(loadHierarchyPivot(file));
				break;
			default:
				cout << "unknown chunktype in hierarchy chunk: " << chunkType << endl;
				file.seekg(0, chunkEnd);
			}
		}
		return hierarchy;
	}

	//#######################################################################################
	//# model
	//#######################################################################################

	Texture loadTexture(ifstream& file)
	{
		Texture texture;
		texture.name = readString(file);
		texture.type = read<uint8>(file);
		texture.value = read<float32>(file);
		return texture;
	}

	MeshMaterial loadMeshMaterial(ifstream& file, uint32 chunkEnd)
	{
		MeshMaterial material;
		material.diffuse = read<RGBA>(file);
		material.diffuse_intensity = read<float32>(file);
		material.specular = read<RGBA>(file);
		material.specular_intensity = read<float32>(file);
		material.emit = read<float32>(file);
		material.alpha = read<float32>(file);

		while (file.tellg() < chunkEnd)
		{
			uint32 chunkType = read<uint32>(file);
			uint32 chunkSize = GetChunkSize(read<uint32>(file));
			uint32 chunkEnd = (long)file.tellg() + chunkSize;

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
		header.type = read<uint8>(file);
		header.meshName = readString(file);
		header.parentPivot = read<uint16>(file);
		header.faceCount = read<uint32>(file);
		header.vertCount = read<uint32>(file);
		return header;
	}

	Mesh loadMesh(ifstream& file, uint32 chunkEnd)
	{
		Mesh mesh;
		while (file.tellg() < chunkEnd)
		{
			uint32 chunkType = read<uint32>(file);
			uint32 chunkSize = GetChunkSize(read<uint32>(file));
			uint32 chunkEnd = (long)file.tellg() + chunkSize;

			switch (chunkType)
			{
			case 2:
				mesh.header = loadMeshHeader(file);
				break;
			case 3:
				while (file.tellg() < chunkEnd)
					mesh.vertices.push_back(read<f32vec3>(file));
				break;
			case 4:
				while (file.tellg() < chunkEnd)
					mesh.normals.push_back(read<f32vec3>(file));
				break;
			case 5:
				while (file.tellg() < chunkEnd)
					mesh.faces.push_back(read<i32vec3>(file));
				break;
			case 6:
				while (file.tellg() < chunkEnd)
					mesh.uvCoords.push_back(read<f32vec2>(file));
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

	W4DModel loadModel(ifstream& file, uint32 chunkEnd)
	{
		W4DModel model;
		model.name = readString(file);
		model.hieraName = readString(file);

		while (file.tellg() < chunkEnd)
		{
			uint32 chunkType = read<uint32>(file);
			uint32 chunkSize = GetChunkSize(read<uint32>(file));
			uint32 chunkEnd = (long)file.tellg() + chunkSize;

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
		return model;
	}

	void W4DLoader::Load(const char * name)
	{
		ifstream file(name, ios::binary);
		long size = getFStreamSize(file);

		while (file.tellg() < size)
		{
			uint32 chunkType = read<uint32>(file);
			uint32 chunkSize = GetChunkSize(read<uint32>(file));
			uint32 chunkEnd = (long)file.tellg() + chunkSize;

			switch (chunkType)
			{
			case 0:
				loadModel(file, chunkEnd);
				break;
			case 256:
				loadHierarchy(file, chunkEnd);
				break;

			default:
				cout << "unknown chunktype in file: " << chunkType << endl;
				file.seekg(0, chunkEnd);
			}
		}
	}
}
