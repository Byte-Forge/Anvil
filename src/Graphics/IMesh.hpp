/*
************************************
* Copyright (C) 2016 ByteForge
* IMesh.hpp
************************************
*/

#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace anvil
{
	class IMesh
	{
	public:
		struct MeshVertexInfluences
		{
			std::uint16_t boneIdx;
			std::uint16_t boneInf;
		};

		std::uint8_t m_type;
		// 0->normal mesh
		// 1->normal mesh - two sided
		// 2->normal mesh - camera oriented
		// 128->skin
		// 129->skin - two sided

		std::string m_meshName;
		std::uint16_t m_materialID;
		std::uint16_t m_parentPivot;
		glm::uint32 m_faceCount;
		glm::uint32 m_vertCount;

		std::vector<glm::f32vec3> m_vertices;
		std::vector<glm::f32vec3> m_normals;
		std::vector<glm::f32vec2> m_uvCoords;
		std::vector<glm::i32vec3> m_faces;
		std::vector<MeshVertexInfluences> m_vertInfs;

		virtual void Update() = 0;
	};
}