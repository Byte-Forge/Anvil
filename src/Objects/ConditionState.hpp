//
// Created by michael on 22.11.15.
//
#pragma once
#include <map>
#include <string>

namespace hpse
{
	class Variant
	{
	public:
		void SetModel(std::string model);
		void AddTexReplace(std::string tex, std::string replace);
	private:
		std::string m_model;
		std::map <const std::string, std::string> m_texReplaces; //textures that should be replaced by another
		std::map <const std::string, std::string> m_animations;
		std::map <const std::string, std::string> m_sounds;
		std::map <const std::string, std::string> props; //entities bound to a pivot of the model hierarchy
	};
}

