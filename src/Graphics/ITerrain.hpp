#pragma once
#include "IRenderable.hpp"
#include "ITexture.hpp"
#include "Quadtree.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace hpse
{
	class ITerrain : public IRenderable
	{
	public:
		ITerrain(std::uint32_t width, std::uint32_t height);

		int GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);
		void SetMaterial(glm::vec3 &pos, float radius, int material);
		void SetHeight(glm::vec3 &pos, float radius, float height);
		inline int GetPolycount()
		{
			return static_cast<int>(m_faces.size() / 3);
		}
	protected:
		void Generate();
		void ComputeNormals(std::vector<std::vector<glm::vec3>> &normals);
		void UpdateBufferData();
		void UpdateTextures();

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