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
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace anvil
{
    namespace GL
    {
        class Texture : public ITexture
        {
        public:
            ~Texture();
			Texture & operator=(const Texture&) = delete;

			void CreateArray(size_t size, size_t levels,int width, int height, const gli::format format, const gli::swizzles swizzles);
			bool SetLevel(int level, const gli::texture& tex);
			bool Load(const gli::texture& tex);
            void Bind();
        private:
			GLuint CreateHandle(const gli::texture& tex);
            GLuint m_handle;
			GLenum m_target;

			static gli::gl GL;
        };
    }
}

