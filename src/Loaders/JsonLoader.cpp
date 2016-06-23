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

		const auto& node = d["material"];
		if (node.HasMember("displacement_factor"))
			mat->SetDisplacementFactor(node["displacement_factor"].GetDouble());
		if (node.HasMember("uPerSec"))
			mat->SetUPerSecond(node["uPerSec"].GetDouble());
		if (node.HasMember("vPerSec"))
			mat->SetVPerSecond(node["vPerSec"].GetDouble());
		if (node.HasMember("displacement_factor"))
			mat->SetDisplacementFactor(node["displacement_factor"].GetDouble());

		if (node.HasMember("albedo"))
			mat->SetAlbedoTexture(node["albedo"].GetString());
		else
			throw AnvilException("Material file has no albedo texture: " + path, __FILE__, __LINE__);
		if (node.HasMember("normal"))
			mat->SetNormalTexture(node["normal"].GetString());
		if (node.HasMember("specular"))
			mat->SetSpecularTexture(node["specular"].GetString());
		if (node.HasMember("displacement"))
			mat->SetDisplacementTexture(node["displacement"].GetString());
		if (node.HasMember("ambient_occ"))
			mat->SetAmbientOcclusionTexture(node["ambient_occ"].GetString());
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
		const auto& node = d["entity"];
		if (node.IsObject())
		{
			if (node.HasMember("parent"))
				ent = std::make_shared<Entity>(Core::GetCore()->GetResources()->GetEntity(node["parent"].GetString()));
			else
				ent = std::make_shared<Entity>();

			Entity::KindOf kO = Entity::KindOf();

			if (node.HasMember("kindOfs"))
			{
				const Value& arr = node["kindOfs"];
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
				}
			}
			ent->SetKindOfs(kO);

			if (node.HasMember("speed"))
			{
				ent->SetSpeed(d["entity"]["speed"].GetDouble());
			}

			if (node.HasMember("modelConditionStates") && node["modelConditionStates"].IsArray())
			{
				std::shared_ptr<Entity::ModelConditionState> state;
				for (unsigned int i = 0; i < node["modelConditionStates"].Size(); i++)
				{
					std::string stateName = node["modelConditionStates"][i]["name"].GetString();
					state = std::make_shared<Entity::ModelConditionState>();
					ent->AddModelConditionState(stateName, state);
					if (node["modelConditionStates"][i].HasMember("scale"))
					{
						state->scale = d["entity"]["modelConditionStates"][i]["scale"].GetDouble();
					}
					
					state->modelName = node["modelConditionStates"][i]["model"].GetString();
					if (node["modelConditionStates"][i].HasMember("skl_path"))
						state->hierarchyPath = node["modelConditionStates"][i]["skl_path"].GetString();

					if (node["modelConditionStates"][i].HasMember("materials") && node["modelConditionStates"][i]["materials"].IsArray())
					{
						for (int j = 0; j < node["modelConditionStates"][i]["materials"].Size(); j++)
						{
							state->materials.insert({ node["modelConditionStates"][i]["materials"][j]["mesh"].GetString(), std::make_tuple(node["modelConditionStates"][i]["materials"][j]["material"].GetString(), nullptr) });
						}
					}
				}
			}
			if (node.HasMember("animationStates") && node["animationStates"].IsArray())
			{
				std::shared_ptr<Entity::AnimationState> state;
				for (unsigned int i = 0; i < node["animationStates"].Size(); i++)
				{
					std::string stateName = node["animationStates"][i]["name"].GetString();
					state = std::make_shared<Entity::AnimationState>();
					ent->AddAnimationState(stateName, state);

					if (node["animationStates"][i].HasMember("animations") && node["animationStates"][i]["animations"].IsArray())
					{
						for (unsigned int j = 0; j < node["animationStates"][i]["animations"].Size(); j++)
						{
							Entity::AnimationStruct ani = Entity::AnimationStruct();
							ani.animationName = node["animationStates"][i]["animations"][j]["animation"].GetString();
							std::string mode = node["animationStates"][i]["animations"][j]["animationMode"].GetString();
							if (mode == "LOOP")
								ani.mode = Entity::ANIMATION_MODE::LOOP;
							else if (mode == "MANUAL")
								ani.mode = Entity::ANIMATION_MODE::MANUAL;
							else if (mode == "ONCE")
								ani.mode = Entity::ANIMATION_MODE::ONCE;
							if (node["animationStates"][i]["animations"][j].HasMember("speed"))
							{
								ani.speed = d["entity"]["animationStates"][i]["animations"][j]["speed"].GetDouble();
							}
							state->animations.push_back(ani);
						}
					}
				}
			}
			if (node.HasMember("childs") && node["childs"].IsArray())
			{
				for (unsigned int i = 0; i < node["childs"].Size(); i++)
				{
					Entity::Child child = Entity::Child();
					const auto& c = node["childs"][i];
					if (c.HasMember("name"))
					{
						child.name = c["name"].GetString();
					}
					if (c.HasMember("position"))
					{
						const auto& pos = c["position"];
						if (pos.HasMember("x"))
							child.position.x = pos["x"].GetDouble();
						if (pos.HasMember("y"))
							child.position.y = pos["y"].GetDouble();
						if (pos.HasMember("z"))
							child.position.z = pos["z"].GetDouble();
					}
					if (c.HasMember("rotation"))
					{
						const auto& rot = c["rotation"];
						if (rot.HasMember("x"))
							child.rotation.x = rot["x"].GetDouble();
						if (rot.HasMember("y"))
							child.rotation.y = rot["y"].GetDouble();
						if (rot.HasMember("z"))
							child.rotation.z = rot["z"].GetDouble();
					}
					if (c.HasMember("scale"))
					{
						child.scale = c["scale"].GetDouble();
					}
					ent->AddChild(child);
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
		const auto& node = d["particlesystem"];
		if (node.IsObject())
		{
			if (node.HasMember("lifetime"))
			{
				particleSys->SetLifetime(node["lifetime"].GetInt());
			}
			if (node.HasMember("interval"))
			{
				particleSys->SetSpawnInterval(node["interval"].GetInt());
			}
			if (node.HasMember("spawnrate"))
			{
				particleSys->SetSpawnRate(node["spawnrate"].GetInt());
			}
		}
	}
	else
		throw AnvilException("Particlesystem file has no particlesystem object: " + path, __FILE__, __LINE__);

	fin.close();

	Core::GetCore()->GetResources()->AddResource(name, particleSys);
}
