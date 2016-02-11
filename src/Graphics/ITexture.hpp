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
    class ITexture : public IResource
    {
    public:
		virtual void CreateArray(int size, int levels,int width, int height, const gli::format format) = 0;
		virtual bool SetLevel(int level, const gli::texture& tex) = 0;
        virtual bool Load(const gli::texture& tex) = 0;
        virtual void Bind() = 0;
    };
}




