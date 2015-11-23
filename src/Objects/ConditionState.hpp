//
// Created by michael on 22.11.15.
//
#pragma once
#include <map>
#include <string>
#include <vector>

namespace hpse
{
	enum States
	{
		DEFAULT,
		DIE,
		WALK,
		RUN,
		DAMAGED,
		REALLY_DAMAGED,
		DESTROYED,
		BURNING,
	};

	class ConditionState
	{
	public:
		void SetModel(std::string model);
		void ReplaceTexture(std::string tex, std::string replace);
		void AddAnimation(std::string animation);
		void AddSound(std::string sound);
		void AddProp(std::string pivot, std::string prop);
		void HideProp(std::string prop);

	private:
		std::string m_model = NULL;
		std::map <std::string, std::string> m_texReplaces; //textures that should be replaced by another
		std::vector<std::string> m_animations;
		std::vector<std::string> m_sounds;
		std::map <std::string, std::string> m_props; //entities bound to a pivot of the model hierarchy
		std::vector<std::string> m_hide_props;
	};
}

