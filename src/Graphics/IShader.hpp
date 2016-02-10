/*
************************************
* Copyright (C) 2016 ByteForge
* IShader.hpp
************************************
*/

#pragma once
#include <string>

namespace anvil
{
    class IShader
    {
    public:
        virtual void Load(const std::string& vertShader, const std::string& fragShader) = 0;
        virtual void Load(const std::string& vertShader, const std::string& geoShader, const std::string& fragShader) = 0;
		virtual void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader) = 0;
		virtual void Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader) = 0;
		virtual void Define(const std::string& macro) = 0;
		virtual void Define(const std::string& macro, const std::string& value) = 0;
		virtual void Compile() = 0;
        virtual void Use() = 0;
		virtual std::uint32_t GetUniformLocation(const std::string& id) = 0;
    };
}



