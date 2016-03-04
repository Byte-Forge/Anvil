/*
************************************
* Copyright (C) 2016 ByteForge
* ITerrain.hpp
************************************
*/

#pragma once
#include "IRenderable.hpp"
#include "ITexture.hpp"
#include "Quadtree.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace anvil
{
	/**
	 * @class	ITerrain
	 *
	 * @brief	A terrain.
	 */
	class ITerrain : public IRenderable
	{
	public:

		/**
		 * @fn	ITerrain::ITerrain(std::uint32_t width, std::uint32_t height);
		 *
		 * @brief	Constructor.
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 */
		ITerrain(std::uint32_t width, std::uint32_t height);

		/**
		 * @fn	int ITerrain::GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);
		 *
		 * @brief	Gets mouse position in world space.
		 * 			
		 * @param	mousePos   	The mouse position.
		 * @param [in,out]	pos	The position.
		 *
		 * @return	The mouse position in world space.
		 */
		int GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);

		/**
		 * @fn	void ITerrain::SetMaterial(glm::vec3 &pos, float radius, int material);
		 *
		 * @brief	Sets a material.
		 *
		 * @param [in,out]	pos	The position.
		 * @param	radius	   	The radius.
		 * @param	material   	The material.
		 */
		void SetMaterial(glm::vec3 &pos, float radius, int material);

		/**
		 * @fn	void ITerrain::SetHeight(glm::vec3 &pos, float radius, float height);
		 *
		 * @brief	Sets a height.
		 *
		 * @param [in,out]	pos	The position.
		 * @param	radius	   	The radius.
		 * @param	height	   	The height.
		 */
		void SetHeight(glm::vec3 &pos, float radius, float height);

		inline int GetPolycount() { return static_cast<int>(m_faces.size() / 3); }

	protected:
		void Generate();
		void ComputeNormals(std::vector<std::vector<glm::vec3>> &normals);
		void CreateHeightmap();
		void UpdateBufferData();
		void UpdateTextures();

	protected:
		std::shared_ptr<ITexture> m_diff;
		std::shared_ptr<ITexture> m_nrm;
		std::shared_ptr<ITexture> m_spec;
		std::shared_ptr<ITexture> m_disp;
		std::shared_ptr<ITexture> m_ambi;

		std::uint32_t m_width, m_height;
		std::vector<std::vector<float>> m_heightmap;
		std::vector<std::string> m_terrainMaterials;
		std::vector<std::vector<glm::vec3>> m_materialmap;
		std::shared_ptr<Quadtree> m_quadtree;

		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec2> m_uvs;
		std::vector<glm::vec3> m_normals;
		std::vector<std::uint32_t> m_faces;
		std::vector<glm::vec3> m_materials;
		bool heightmap_changed = true;
		bool uvs_changed = true;
		bool faces_changed = true;
		bool materials_changed = true;
	};
}