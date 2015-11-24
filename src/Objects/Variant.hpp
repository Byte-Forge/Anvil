//
// Created by michael on 22.11.15.
//
#pragma once
#include <map>
#include <string>
#include "ConditionState.hpp"

namespace hpse
{
	class Variant
	{
	public:
		Variant(std::map<std::string, std::string> props);
		~Variant();

		void ReplaceTexture(std::string tex, std::string replace);
		void AddProp(std::string pivot, std::string prop);

	private:
		std::map <std::string, std::string> m_textureReplaces;
		std::map <std::string, std::string> m_props;
	};
}

