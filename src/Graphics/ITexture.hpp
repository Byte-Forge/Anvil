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
        virtual bool Load(const gli::texture& tex) = 0;
		virtual bool Load(std::vector<gli::texture> textures) = 0;
        virtual void Bind() = 0;
    };
}




