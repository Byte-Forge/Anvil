/*
************************************
* Copyright (C) 2016 ByteForge
* JsonLoader.cpp
************************************
*/

#include "JsonLoader.hpp"
#include "../Graphics/Material.hpp"
#include "../Core.hpp"
#include "../Core/ResourceHandler.hpp"
#include "../Util.hpp"
#include "../Exception.hpp"
#include "../Objects/Entity.hpp"
#include "../Graphics/IParticleSystem.hpp"
#include <iostream>
#include <tuple>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

using namespace anvil;
using namespace rapidjson;

void JsonLoader::LoadMaterial(const std::string &name, const std::string &path)
{
	std::shared_ptr<Material> mat;

	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		throw AnvilException("Failed to open material file: " + path, __FILE__, __LINE__);
	IStreamWrapper isw(fin);
	Document d;
	ParseResult ok = d.ParseStream(isw);
	if (!ok) 
		throw AnvilException("Failed to parse file: " + path, __FILE__, __LINE__);
	
	if (d.HasMember("material"))
	{
		mat = std::make_shared<Material>();
		if (d["material"].HasMember("displacement_factor"))
			mat->SetDisplacementFactor(d["material"]["displacement_factor"].GetDouble());
		if (d["material"].HasMember("uPerSec"))
			mat->SetUPerSecond(d["material"]["uPerSec"].GetDouble());
		if (d["material"].HasMember("vPerSec"))
			mat->SetVPerSecond(d["material"]["vPerSec"].GetDouble());
		if (d["material"].HasMember("displacement_factor"))
			mat->SetDisplacementFactor(d["material"]["displacement_factor"].GetDouble());
		if (d["material"].HasMember("albedo"))
			mat->SetAlbedoTexture(d["material"]["albedo"].GetString());
		else
			throw AnvilException("Material file has no albedo texture: " + path, __FILE__, __LINE__);
		if (d["material"].HasMember("normal"))
			mat->SetNormalTexture(d["material"]["normal"].GetString());
		if (d["material"].HasMember("specular"))
			mat->SetSpecularTexture(d["material"]["specular"].GetString());
		if (d["material"].HasMember("displacement"))
			mat->SetDisplacementTexture(d["material"]["displacement"].GetString());
		if (d["material"].HasMember("ambient_occ"))
			mat->SetAmbientOcclusionTexture(d["material"]["ambient_occ"].GetString());
	}
	else
		throw AnvilException("Material file has no material object: " + path, __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(name, mat);
}

void JsonLoader::LoadEntity(const std::string &name, const std::string &path)
{
	std::shared_ptr<Entity> ent;

	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		throw AnvilException("Failed to open entity file: " + path, __FILE__, __LINE__);
	IStreamWrapper isw(fin);
	Document d;

	ParseResult ok = d.ParseStream(isw);
	if (!ok) 
		throw AnvilException("Failed to parse file: " + path, __FILE__, __LINE__);

	if (d.HasMember("entity"))
	{
		if (d["entity"].IsObject())
		{
			if (d["entity"].HasMember("parent"))
				ent = std::make_shared<Entity>(Core::GetCore()->GetResources()->GetEntity(d["entity"]["parent"].GetString()));
			else
				ent = std::make_shared<Entity>();

			Entity::KindOf kO = Entity::KindOf();

			if (d["entity"].HasMember("kindOfs"))
			{
				const Value& arr = d["entity"]["kindOfs"];
				for (Value::ConstValueIterator it = arr.Begin(); it != arr.End(); ++it)
				{
					std::string koStr = it->GetString();
					if(koStr =="MISC")
						kO.MISC = true;
					else if (koStr == "SHRUBBERY")
					{
						if (kO.MISC == true)
							std::cout << "WARNING!: Entity cannot be of type MISC AND SHRUBBERY!!" << std::endl;
						else
							kO.SHRUBBERY = true;
					}
					else if (koStr == "UNIT")
					{
						if (kO.MISC == true)
							std::cout << "WARNING!: Entity cannot be of type MISC AND UNIT!!" << std::endl;
						if (kO.SHRUBBERY == true)
							std::cout << "WARNING!: Entity cannot be of type SHRUBBERY AND UNIT!!" << std::endl;
						else
							kO.UNIT = true;
					}
					else if (koStr == "BUILDING")
					{
						if (kO.MISC == true)
							std::cout << "WARNING!: Entity cannot be of type MISC AND BUILDING!!" << std::endl;
						if (kO.SHRUBBERY == true)
							std::cout << "WARNING!: Entity cannot be of type SHRUBBERY AND BUILDING!!" << std::endl;
						if (kO.UNIT == true)
							std::cout << "WARNING!: Entity cannot be of type UNIT AND BUILDING!!" << std::endl;
						else
							kO.BUILDING = true;
					}
					else if (koStr == "ANIMATED")
					{
						kO.ANIMATED = true;
					}
				}
			}
			ent->SetKindOfs(kO);

			if (d["entity"].HasMember("modelConditionStates") && d["entity"]["modelConditionStates"].IsArray())
			{
				std::shared_ptr<Entity::ModelConditionState> state;
				for (int i = 0; i < d["entity"]["modelConditionStates"].Size(); i++)
				{
					std::string stateName = d["entity"]["modelConditionStates"][i]["name"].GetString();
					state = std::make_shared<Entity::ModelConditionState>();
					ent->AddModelConditionState(stateName, state);
					if (d["entity"]["modelConditionStates"][i].HasMember("scale"))
					{
						std::string scale = d["entity"]["modelConditionStates"][i]["scale"].GetString();
						state->scale = ::atof(scale.c_str());
					}
					
					state->modelName = d["entity"]["modelConditionStates"][i]["model"].GetString();
					if (d["entity"]["modelConditionStates"][i].HasMember("skl_path"))
						state->hierarchyPath = d["entity"]["modelConditionStates"][i]["skl_path"].GetString();

					if (d["entity"]["modelConditionStates"][i].HasMember("materials") && d["entity"]["modelConditionStates"][i]["materials"].IsArray())
					{
						for (int j = 0; j < d["entity"]["modelConditionStates"][i]["materials"].Size(); j++)
						{
							state->materials.insert({ d["entity"]["modelConditionStates"][i]["materials"][j]["mesh"].GetString(), std::make_tuple(d["entity"]["modelConditionStates"][i]["materials"][j]["material"].GetString(), nullptr) });
						}
					}
				}
			}
			if (d["entity"].HasMember("animationStates") && d["entity"]["animationStates"].IsArray())
			{
				std::shared_ptr<Entity::AnimationState> state;
				for (int i = 0; i < d["entity"]["animationStates"].Size(); i++)
				{
					std::string stateName = d["entity"]["animationStates"][i]["name"].GetString();
					state = std::make_shared<Entity::AnimationState>();
					ent->AddAnimationState(stateName, state);

					state->animationName = d["entity"]["animationStates"][i]["animation"].GetString();
					std::string mode = d["entity"]["animationStates"][i]["animationMode"].GetString();
					if (mode == "LOOP")
						state->mode = Entity::ANIMATION_MODE::LOOP;
					else if (mode == "MANUAL")
						state->mode = Entity::ANIMATION_MODE::MANUAL;
				}
			}
		}
	}
	else
		throw AnvilException("Entity file has no entity object: " + path, __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(name, ent);
}

void JsonLoader::LoadParticlesystem(const std::string & name, const std::string & path)
{
	std::shared_ptr<IParticleSystem> particleSys;

	std::ifstream fin(path, std::ios::in);
	if (fin.fail())
		throw AnvilException("Failed to open particlesystem file: " + path, __FILE__, __LINE__);
	IStreamWrapper isw(fin);
	Document d;
	ParseResult ok = d.ParseStream(isw);
	if (!ok) 
		throw AnvilException("Failed to parse file: " + path, __FILE__, __LINE__);

	if (d.HasMember("particlesystem"))
	{
		if (d["particlesystem"].IsObject())
		{
			if (d["particlesystem"].HasMember("lifetime"))
			{
				particleSys->SetLifetime(d["particlesystem"]["lifetime"].GetInt());
			}
			if (d["particlesystem"].HasMember("interval"))
			{
				particleSys->SetSpawnInterval(d["particlesystem"]["interval"].GetInt());
			}
			if (d["particlesystem"].HasMember("spawnrate"))
			{
				particleSys->SetSpawnRate(d["particlesystem"]["spawnrate"].GetInt());
			}
		}
	}
	else
		throw AnvilException("Particlesystem file has no particlesystem object: " + path, __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(name, particleSys);
}
