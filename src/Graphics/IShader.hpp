//
// Created by stephan on 28.10.15.
//
#pragma once
#include <string>

namespace hpse
{
    class IShader
    {
    public:
        virtual void Load(const std::string& vertShader, const std::string& fragShader) = 0;
        virtual void Load(const std::string& vertShader, const std::string& geoShader,
                              const std::string& fragShader) = 0;
        virtual void Compile() = 0;
        virtual void Bind() = 0;
    };
}



