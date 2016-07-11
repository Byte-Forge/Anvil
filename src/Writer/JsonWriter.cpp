/*
************************************
* Copyright (C) 2016 ByteForge
* JsonWriter.cpp
************************************
*/

#include "JsonWriter.hpp"
#include "../Core/Options.hpp"
#include <fstream>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>

using namespace anvil;
using namespace rapidjson;

void JsonWriter::SaveOptions(const std::string& path)
{
	Document d;
	auto& allocator = d.GetAllocator();
	d.SetObject();
	Value options(kObjectType);
	{
		Value width(Options::GetWidth());
		options.AddMember("width", width, allocator);
	}
	{
		Value height(Options::GetHeight());
		options.AddMember("height", height, allocator);
	}
	{
		Value fullscreen(Options::GetFullscreen());
		options.AddMember("fullscreen", fullscreen, allocator);
	}
	{
		Value tessfactor(Options::GetTessfactor());
		options.AddMember("tessfactor", tessfactor, allocator);
	}
	{
		Value tessfactor(Options::GetSampleFactor());
		options.AddMember("samplefactor", tessfactor, allocator);
	}
	{
		Value minRender(Options::GetMinimalRendering());
		options.AddMember("minimalRendering", minRender, allocator);
	}
	{
		Value shadows(Options::GetShadows());
		options.AddMember("shadows", shadows, allocator);
	}
	d.AddMember("options", options, allocator);

	std::ofstream ofs(path);
	OStreamWrapper osw(ofs);
	PrettyWriter<OStreamWrapper> writer(osw);
	d.Accept(writer);
}