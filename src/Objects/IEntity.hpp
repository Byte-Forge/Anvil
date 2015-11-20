//
// Created by michael on 19.11.15.
//
#pragma once
#include "../Core/IResource.hpp"
#include "../Graphics/GL/Model.hpp"

namespace hpse
{
    class IEntity : public IResource
    {
	private:
		GL::Model m_model;
    };
}


