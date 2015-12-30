//
// Created by stephan on 27.10.15.
//
#pragma once
#include <stdint.h>
#include <memory>
#include <gli/gli.hpp>
#include <gli/texture.hpp>
#include <vector>
#include "../Core/IResource.hpp"

namespace hpse
{
    class ITexture : public IResource
    {
    public:
        virtual bool Load(const gli::texture& tex) = 0;
		virtual bool Load(std::vector<gli::texture> textures) = 0;
        virtual void Bind() = 0;
    };
}




