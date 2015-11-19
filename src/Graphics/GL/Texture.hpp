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
			Texture();
            Texture(GLuint handle);
            ~Texture();

            //data is expected to be 32 bit RGBA
            void Update(int width, int height, const uint8_t* data);
            void Bind();
        private:
            GLuint m_handle;
        };
    }
}

