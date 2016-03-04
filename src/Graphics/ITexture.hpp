/*
************************************
* Copyright (C) 2016 ByteForge
* ITexture.hpp
************************************
*/

#pragma once
#include <stdint.h>
#include <memory>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <vector>
#include "../Core/IResource.hpp"

namespace anvil
{
    /**
     * @class	ITexture
     *
     * @brief	A texture.
     */
    class ITexture : public IResource
    {
    public:

		/**
		 * @fn	virtual void ITexture::CreateArray(size_t size, size_t levels, int width, int height, const gli::format format, const gli::swizzles swizzles) = 0;
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
		virtual void CreateArray(size_t size, size_t levels, int width, int height, const gli::format format, const gli::swizzles swizzles) = 0;

		/**
		 * @fn	virtual bool ITexture::SetLevel(int level, const gli::texture& tex) = 0;
		 *
		 * @brief	Sets a level.
		 *
		 * @param	level	The level.
		 * @param	tex  	The tex.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		virtual bool SetLevel(int level, const gli::texture& tex) = 0;

        /**
         * @fn	virtual bool ITexture::Load(const gli::texture& tex) = 0;
         *
         * @brief	Loads the given tex.
         *
         * @param	tex	The tex to load.
         *
         * @return	true if it succeeds, false if it fails.
         */
        virtual bool Load(const gli::texture& tex) = 0;

        /**
         * @fn	virtual void ITexture::Bind() = 0;
         *
         * @brief	Binds this object.
         */
        virtual void Bind() = 0;
    };
}




