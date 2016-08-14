/*
************************************
* Copyright (C) 2016 ByteForge
* IShader.cpp
************************************
*/


#include "IShader.hpp"
#include "../Util/FileWatcher.hpp"
#include <iostream>

using namespace anvil;
namespace fs = boost::filesystem;

IShader::IShader() : m_tracked(false)
{

}

void IShader::Load(const std::string &vertShader, const std::string &fragShader)
{
	LoadShader(vertShader, ANVIL_VERT_SHADER);
	LoadShader(fragShader, ANVIL_FRAG_SHADER);
	Link();
}

void IShader::Load(const std::string &vertShader, const std::string& geoShader, const std::string &fragShader)
{
	LoadShader(vertShader, ANVIL_VERT_SHADER);
	LoadShader(geoShader,  ANVIL_GEOM_SHADER);
	LoadShader(fragShader, ANVIL_FRAG_SHADER);
	Link();
}

void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& fragShader)
{
	LoadShader(vertShader,			ANVIL_VERT_SHADER);
	LoadShader(tessControlShader,	ANVIL_TESC_SHADER);
	LoadShader(tessEvalShader,		ANVIL_TESE_SHADER);
	LoadShader(fragShader,			ANVIL_FRAG_SHADER);
	Link();
}

void IShader::Load(const std::string& vertShader, const std::string& tessControlShader, const std::string& tessEvalShader, const std::string& geoShader, const std::string& fragShader)
{
	LoadShader(vertShader,			ANVIL_VERT_SHADER);
	LoadShader(tessControlShader,	ANVIL_TESC_SHADER);
	LoadShader(tessEvalShader,		ANVIL_TESE_SHADER);
	LoadShader(geoShader,			ANVIL_GEOM_SHADER);
	LoadShader(fragShader,			ANVIL_FRAG_SHADER);
	Link();
}

void IShader::LoadShader(const std::string& file, const ShaderType type)
{
	auto reload = [this](const fs::path &path) {
		if (m_tracked)
		{
			std::cout << path << " needs recompile" << std::endl;
			m_shouldReload = true;
		}
	};

	if (!m_tracked)
	{
		FileWatcher::AddPath(fs::path(file),reload);
		m_files[file] = type;
	}
}

void IShader::Ready()
{
	m_tracked = true;
}

void IShader::Update()
{
	if (m_shouldReload)
	{
		for (const auto& file : m_files)
		{
			LoadShader(file.first, file.second);
		}
		Link();
		m_uniforms.clear();
		m_ubos.clear();
		for (auto ubo : m_ubo_indices)
		{
			AttachUBO(ubo.first, ubo.second);
		}
		m_shouldReload = false;
	}
}