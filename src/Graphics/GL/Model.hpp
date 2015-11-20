//
// Created by michael on 19.11.15.
//
#pragma once
#include "../IModel.hpp"

namespace hpse
{
    namespace GL
    {
        class Model : public IModel 
        {
        public:
			Model();
            ~Model();

            void Render();
        };
    }
}

