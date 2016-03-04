/*
************************************
* Copyright (C) 2016 ByteForge
* Terrain.hpp
************************************
*/

#pragma once
#include "../ITerrain.hpp"
#include "../Quadtree.hpp"
#include "../Material.hpp"
#include "BufferGL.hpp"
#include "flextGL.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace anvil
{
    namespace GL
    {
        class Terrain : public ITerrain
        {
        public:
            Terrain(std::uint32_t width, std::uint32_t height);
			~Terrain();
			
            void Render(int mode,IShader& shader);
            void Update();
        private:
			//rendering stuff
			glm::mat4 m_mvp;
			glm::mat4 m_mod;
			glm::mat3 m_mv3x3;

			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_fbo, m_mbo;
        };
    }
}




