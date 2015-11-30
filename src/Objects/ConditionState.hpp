//
// Created by michael on 22.11.15.
//
#pragma once
#include <map>
#include <string>
#include <vector>

namespace hpse
{
	enum State
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
		void ReplaceTexture(std::string tex, std::string replace);
		void AddProp(std::string pivot, std::string prop);
		void AddFX(std::string pivot, std::string fx);
		void AddAnimation(std::string animation);
		void AddSound(std::string sound);

	private:
		std::map <std::string, std::string> m_textureReplaces; 
		std::map <std::string, std::string> m_boneFXs; 
		std::map <std::string, std::string> m_props;
		std::vector<std::string> m_animations;
		std::vector<std::string> m_sounds;
	};
}

