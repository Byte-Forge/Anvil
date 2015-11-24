//
// Created by michael on 19.11.15.
//
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "ConditionState.hpp"
#include "Variant.hpp"
#include "../Core/IResource.hpp"


namespace hpse
{
    class IEntity : public IResource
    {
	public:
		IEntity(std::string name);
		~IEntity();
		void SetModel(std::string model);
		std::shared_ptr<IResource> GetModel(); 
		void SetWeaponLaunchBone(std::string bone);
		void AddProp(std::string pivot, std::string prop);
		void AddFX(std::string pivot, std::string fx);
		void AddVariant(Variant var);
		void AddConditionState(State s, ConditionState state);

	private:
		std::string m_name = NULL;
		std::string m_w4dModel = NULL;
		std::string m_weaponLaunchBone = NULL;
		std::map <std::string, std::string> m_props;
		std::map <std::string, std::string> m_boneFXs;
		std::vector <Variant> m_variants;
		std::map <State, ConditionState> m_conditionStates;
    };
}


