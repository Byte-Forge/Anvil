#include "Options.hpp"
#include <fstream>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
using namespace anvil;
using namespace rapidjson;

bool Options::s_fullscreen			= false;
unsigned int Options::s_width		= 800;
unsigned int Options::s_height		= 600;
int Options::s_tessFactor			= 32;

bool Options::Load(const std::string& path)
{
	bool result = true;
	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		return false;

	IStreamWrapper isw(fin);
	Document d;
	d.ParseStream(isw);

	if (d.HasMember("options"))
	{
		if (d["options"].HasMember("width"))
			s_width = d["options"]["width"].GetUint();
		else
			result = false;
		if (d["options"].HasMember("height"))
			s_height = d["options"]["height"].GetUint();
		else
			result = false;
		if (d["options"].HasMember("tessfactor"))
			s_tessFactor = d["options"]["tessfactor"].GetInt();
		else
			result = false;
		if (d["options"].HasMember("fullscreen"))
			s_fullscreen = d["options"]["fullscreen"].GetBool();
		else
			result = false;
	}
	else
	{
		result = false;
	}
	fin.close();

	return result;
}

void Options::Save(const std::string& path)
{
	Document d;
	auto& allocator = d.GetAllocator();
	d.SetObject();
	Value options(kObjectType);
	{
		Value width(s_width);
		options.AddMember("width", width, allocator);
	}
	{
		Value height(s_height);
		options.AddMember("height", height, allocator);
	}
	{
		Value fullscreen(s_fullscreen);
		options.AddMember("fullscreen", fullscreen, allocator);
	}
	{
		Value tessfactor(s_tessFactor);
		options.AddMember("tessfactor", tessfactor, allocator);
	}
	d.AddMember("options",options, allocator);

	std::ofstream ofs(path);
	OStreamWrapper osw(ofs);
	PrettyWriter<OStreamWrapper> writer(osw);
	d.Accept(writer);
}