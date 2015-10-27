//
// Created by stephan on 27.10.15.
//
#pragma once
#include <stdint.h>
#include <memory>

namespace hpse
{
    class ITexture
    {
    public:
        virtual void Update(int width,int height,const uint8_t* data) = 0;
        virtual void Bind() = 0;
    };
}




