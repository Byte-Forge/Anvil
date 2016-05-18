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
		 * @fn	virtual void IMesh::Render(IShader& shader) = 0;
		 *
		 * @brief	Renders the given shader.
		 *
		 * @param [in,out]	shader	The shader.
		 */
		virtual void Render(IShader& shader) = 0;


		/**
		* @fn	virtual void IMesh::Init() = 0;
		*
		* @brief	Initializes the Mesh for rendering.
		*/
		virtual void Init() = 0;

		inline void SetType(std::uint8_t type) { m_type = type; }
		inline void SetName(const std::string& meshName) { m_meshName = meshName; }
		inline std::string GetName() { return m_meshName; }
		inline void SetMaterialID(std::uint16_t materialID) { m_materialID = materialID; }
		inline void SetParentPivot(std::uint32_t parentPivot) { m_parentPivot = parentPivot; }
		inline void SetFaceCount(glm::uint32 faceCount) { m_faceCount = faceCount; }
		inline void SetVerticesCount(glm::uint32 vertCount) { m_vertCount = vertCount; }
		inline void SetVertices(std::vector<glm::f32vec3> vertices) { m_vertices = vertices; }
		inline void SetNormals(std::vector<glm::f32vec3> normals) { normals = m_normals; }
		inline void SetUVCoords(std::vector<glm::f32vec2> uvCoords) { m_uvCoords = uvCoords; }
		inline void SetFaces(std::vector<glm::i32vec3> faces) { m_faces = faces; }
		inline void SetVertInfs(std::vector<glm::i32vec2> vertInfs) { m_vertInfs = vertInfs; }

	protected:
		std::uint8_t m_type;
		// 0->normal mesh
		// 1->normal mesh - two sided
		// 2->normal mesh - camera oriented
		// 128->skin
		// 129->skin - two sided

		std::string m_meshName;
		std::uint32_t m_materialID;
		std::uint32_t m_parentPivot;
		glm::uint32 m_faceCount;
		glm::uint32 m_vertCount;

		std::vector<glm::f32vec3> m_vertices;
		std::vector<glm::f32vec3> m_normals;
		std::vector<glm::f32vec2> m_uvCoords;
		std::vector<glm::i32vec3> m_faces;
		std::vector<glm::i32vec2> m_vertInfs;
	};
}