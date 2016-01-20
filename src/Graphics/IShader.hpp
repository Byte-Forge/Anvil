//
// Created by stephan on 28.10.15.
//
#pragma once
#include <string>

namespace hpse
{
	enum ShaderMode
	{
		DEFAULT = 0,
		WIREFRAME = 1,
		NORMALS = 2 
	};

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



