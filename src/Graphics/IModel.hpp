//
// Created by michael on 19.11.15.
//
#pragma once
#include <map>
#include "../Types/W4D.hpp"

namespace hpse
{
    class IModel : public IResource
    {
    public:
        virtual void Render() = 0;
	private:
		std::map<const std::string, Variant> m_variants;
    };

	class Variant
	{
	private:
		//put the instances here??
		W4DModel m_model;
		std::map<const std::string, const std::string> m_textures;
		std::map<const std::string, const std::string> m_animations;
	};
}




