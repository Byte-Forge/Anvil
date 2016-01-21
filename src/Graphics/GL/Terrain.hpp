//
// Created by stephan on 14.12.15.
//

#pragma once
#include "../IRenderable.hpp"
#include "../ITexture.hpp"
#include "../Quadtree.hpp"
#include "../Material.hpp"
#include "flextGL.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace hpse
{
    namespace GL
    {
        class Terrain : public IRenderable
        {
        public:
            Terrain(std::uint32_t width, std::uint32_t height);
			~Terrain();
			int GetMousePositionInWorldSpace(glm::vec2 mousePos, glm::vec3 &pos);
			void SetTerrainHeight(glm::vec3 &pos, float height, float radius);

            void Render(int mode);
            void Update();

        private:
			std::uint32_t m_width, m_height;
			std::vector<float> m_heightmap;
			std::vector<std::string> m_terrainMaterials;
			std::vector<glm::vec3> m_materialmap;
			std::shared_ptr<Quadtree> m_quadtree;

			bool heightmap_changed = true;
			bool uvs_changed = true;
			bool faces_changed = true;
			bool materials_changed = true;

			//rendering stuff
			std::vector<GLuint> m_tessLevelIDs, m_lightIDs;

			std::shared_ptr<ITexture> m_diff;
			std::shared_ptr<ITexture> m_nrm;
			std::shared_ptr<ITexture> m_spec;
			std::shared_ptr<ITexture> m_disp;
			std::shared_ptr<ITexture> m_ambi;

			std::vector<GLuint> m_diffIDs, m_nrmIDs, m_specIDs, m_dispIDs, m_ambiIDs;

			glm::mat4 m_mvp;
			glm::mat4 m_mod;
			glm::mat3 m_mv3x3;

			std::vector<GLuint> m_matrixIDs, m_modelMatrixIDs, m_viewMatrixIDs, m_modelView3x3MatrixIDs;

			std::vector<glm::vec3> m_vertices;
			std::vector<glm::vec2> m_uvs;
			std::vector<glm::vec3> m_normals;
			std::vector<std::uint32_t> m_faces;
			std::vector<glm::vec3> m_materials;

			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_uvbo;
			GLuint m_nbo;
			GLuint m_fbo;
			GLuint m_mbo;

			void Generate();
			void ComputeNormals(std::vector<glm::vec3> &normals);
			void UpdateBufferData();
        };
    }
}




