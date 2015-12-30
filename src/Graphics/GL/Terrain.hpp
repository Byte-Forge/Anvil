//
// Created by stephan on 14.12.15.
//

#pragma once
#include "../IRenderable.hpp"
#include "../ITexture.hpp"
#include "../Quadtree.hpp"
#include "flextGL.h"
#include <vector>
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

            void Render();
            void Update();
        private:
			std::uint32_t m_width, m_height;
			std::shared_ptr<Quadtree> m_quadtree;

			bool updated = true;

			GLuint m_lightID;

			std::shared_ptr<ITexture> m_diff;
			std::shared_ptr<ITexture> m_nrm;
			std::shared_ptr<ITexture> m_spec;
			std::shared_ptr<ITexture> m_disp;
			std::shared_ptr<ITexture> m_ambi;

			GLuint m_diffID;
			GLuint m_nrmID;
			GLuint m_specID;
			GLuint m_dispID;
			GLuint m_ambiID;

			GLuint m_matrixID;
			GLuint m_modelMatrixID;
			GLuint m_viewMatrixID;
			GLuint m_modelView3x3MatrixID;

			glm::mat4 m_mvp;
			glm::mat4 m_mod;
			glm::mat3 m_mv3x3;

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
        };
    }
}




