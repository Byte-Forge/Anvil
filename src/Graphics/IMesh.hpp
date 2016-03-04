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
#include "IShader.hpp"
namespace anvil
{
	/**
	 * @class	IMesh
	 *
	 * @brief	A mesh.
	 */
	class IMesh
	{
	public:

		/**
		 * @struct	MeshVertexInfluences
		 *
		 * @brief	How the vertices are influenced by the bone.
		 */
		struct MeshVertexInfluences
		{
			std::uint16_t boneIdx;
			std::uint16_t boneInf;
		};

		/**
		 * @fn	virtual void IMesh::Update() = 0;
		 *
		 * @brief	Updates this mesh (used to create buffers).
		 */
		virtual void Update() = 0;

		/**
		 * @fn	virtual void IMesh::Render(IShader& shader) = 0;
		 *
		 * @brief	Renders the given shader.
		 *
		 * @param [in,out]	shader	The shader.
		 */
		virtual void Render(IShader& shader) = 0;

		inline void SetType(std::uint8_t type) { m_type = type; }
		inline void SetMeshName(const std::string& meshName) { m_meshName = meshName; }
		inline void SetMaterialID(std::uint16_t materialID) { m_materialID = materialID; }
		inline void SetParentPivot(std::uint16_t parentPivot) { m_parentPivot = parentPivot; }
		inline void SetFaceCount(glm::uint32 faceCount) { m_faceCount = faceCount; }
		inline void SetVerticesCount(glm::uint32 vertCount) { m_vertCount = vertCount; }
		inline void SetVertices(std::vector<glm::f32vec3> vertices) { m_vertices = vertices; }
		inline void SetNormals(std::vector<glm::f32vec3> normals) { normals = m_normals; }
		inline void SetUVCoords(std::vector<glm::f32vec2> uvCoords) { m_uvCoords = uvCoords; }
		inline void SetFaces(std::vector<glm::i32vec3> faces) { m_faces = faces; }
		inline void SetVertInfs(std::vector<MeshVertexInfluences> vertInfs) { m_vertInfs = vertInfs; }

	protected:
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
	};
}