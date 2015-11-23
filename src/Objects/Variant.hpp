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
		void SetModel(std::string model);
		void ReplaceTexture(std::string tex, std::string replace);
		void AddProp(std::string pivot, std::string prop);
		void AddConditionState(States state, ConditionState cState);

	private:
		std::string m_model = NULL;
		std::map <std::string, std::string> m_texReplaces; //textures that should be replaced by another
		std::map <std::string, std::string> m_props; //entities bound to a pivot of the model hierarchy
		std::map <States, ConditionState> m_condition_states;
	};
}

