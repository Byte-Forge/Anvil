//
// Created by stephan on 27.10.15.
//
#pragma once
#include <stdint.h>
#include <string>
#include "../ITexture.hpp"
#include <GL/gl.h>

namespace hpse
{
    namespace GL
    {
        class Texture : public ITexture
        {
        public:
            ~Texture();

            bool Load(const gli::texture& tex);
            void Bind();
        private:
            GLuint m_handle;
        };
    }
}

