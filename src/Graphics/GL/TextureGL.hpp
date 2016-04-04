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
        /**
         * @class	Texture
         *
         * @brief	A texture.
         */
        class Texture : public ITexture
        {
        public:

            /**
             * @fn	Texture::~Texture();
             *
             * @brief	Destructor.
             */
            ~Texture();

			Texture & operator=(const Texture&) = delete;

			/**
			 * @fn	void Texture::CreateArray(size_t size, size_t levels,int width, int height, const gli::format format, const gli::swizzles swizzles);
			 *
			 * @brief	Creates an array.
			 *
			 * @param	size		The size.
			 * @param	levels  	The levels.
			 * @param	width   	The width.
			 * @param	height  	The height.
			 * @param	format  	Describes the format to use.
			 * @param	swizzles	The swizzles.
			 */
			void CreateArray(size_t size, size_t levels,int width, int height, const gli::format format, const gli::swizzles swizzles);

			/**
			 * @fn	bool Texture::SetLevel(int level, const gli::texture& tex);
			 *
			 * @brief	Sets a level.
			 *
			 * @param	level	The level.
			 * @param	tex  	The tex.
			 *
			 * @return	true if it succeeds, false if it fails.
			 */
			bool SetLevel(int level, const gli::texture& tex);

			/**
			 * @fn	bool Texture::Load(const gli::texture& tex);
			 *
			 * @brief	Loads the given tex.
			 *
			 * @param	tex	The tex to load.
			 *
			 * @return	true if it succeeds, false if it fails.
			 */
			bool Load(const gli::texture& tex);

            /**
             * @fn	void Texture::Bind();
             *
             * @brief	Binds this object.
             */
            void Bind();

        private:
            GLuint m_handle;
			GLenum m_target;

			static gli::gl GL;
        };
    }
}

