/*
************************************
* Copyright (C) 2016 ByteForge
* Texture.hpp
************************************
*/

#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include "../ITexture.hpp"
#include <GL/gl.h>

namespace anvil
{
    namespace GL
    {
        class Texture : public ITexture
        {
        public:
            ~Texture();
			Texture & operator=(const Texture&) = delete;

			bool Load(const gli::texture& tex);
			bool Load(std::vector<gli::texture> textures);
            void Bind();
        private:
			GLuint CreateHandle(const gli::texture& tex);
            GLuint m_handle;
			GLenum m_target;

			static gli::gl GL;
        };
    }
}

