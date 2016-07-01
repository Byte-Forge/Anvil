/*
************************************
* Copyright (C) 2016 ByteForge
* Options.cpp
************************************
*/

#include "Options.hpp"
#include "../Loaders/JsonLoader.hpp"
#include "../Writer/JsonWriter.hpp"

using namespace anvil;

bool Options::s_fullscreen			= false;
unsigned int Options::s_width		= 800;
unsigned int Options::s_height		= 600;
int Options::s_tessFactor			= 32;
int Options::s_sampleFactor			= 1;

bool Options::Load(const std::string& path)
{
	return JsonLoader::LoadOptions(path);
}

void Options::Save(const std::string& path)
{
	JsonWriter::SaveOptions(path);
}