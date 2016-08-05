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
        /**
         * @class	Terrain
         *
         * @brief	A terrain.
         */
        class Terrain : public ITerrain
        {
        public:

            /**
             * @fn	Terrain::Terrain(std::uint32_t width, std::uint32_t height);
             *
             * @brief	Constructor.
             *
             * @param	width 	The width.
             * @param	height	The height.
             */
            Terrain(std::uint32_t width, std::uint32_t height);

			/**
			 * @fn	Terrain::~Terrain();
			 *
			 * @brief	Destructor.
			 */
			~Terrain();

            /**
             * @fn	void Terrain::Render(IShader& shader, bool minimal);
             *
             * @brief	Renders the given shader.
             *
             * @param [in,out]	shader	The shader.
			 * @param	minimal if it should render with minimal settings
			 *
			 * @return  returns the number of drawn polygons
             */
            size_t Render(IShader& shader, bool minimal);

            /**
             * @fn	void Terrain::Update();
             *
             * @brief	Updates this object.
             */
            void Update();

        private:
			//rendering stuff
			glm::mat3 m_mv3x3;

			GLuint m_vao;
			std::unique_ptr<Buffer> m_vbo, m_uvbo, m_nbo, m_fbo, m_mbo;
        };
    }
}




